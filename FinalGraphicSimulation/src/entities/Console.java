package src.entities;

import src.Panel;


import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;

import javax.imageio.ImageIO;
import javax.swing.JPanel;

import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;

public class Console extends JPanel implements Runnable{

    int xPos = 0;
    int yPos = 0;
    int width = 0;
    int height = 0;
    int numTrucks = 0;
    int leaderID = 0;
    public BufferedImage border;
    public String sentence;
    public int objSpeed;
    public static int objSize;
    public int objDistance;
    public String truckSpeed = "0";
    public String platoonSize = "0";
    public String safetyDistance = "0";

    Thread serverThread;
    Panel panel;
    DatagramSocket serverSocket;
    byte[] receiveData = new byte[123];
    JSONParser parser = new JSONParser();
    
    

    public Console(Panel panel){
        this.panel = panel;
        try {
            this.serverSocket = new DatagramSocket(1123);
        } catch (SocketException e1) {
            e1.printStackTrace();
        }
        getPos();
        getSizes();
        getBorders();
        this.setPreferredSize(new Dimension(width, height));
        this.setDoubleBuffered(true);
        this.setFocusable(true);

        Runtime.getRuntime().addShutdownHook(new Thread() {
            public void run() {
                try {
                    Thread.sleep(200);
                    serverSocket.close();
                    //some cleaning up code...
      
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    e.printStackTrace();
                    
                }
            }
        });

    }
    
    public void startThread(){
        serverThread = new Thread(this);
        serverThread.start();
    }

    public void getBorders(){
        try {
            border = ImageIO.read(getClass().getResourceAsStream("/src/res/border.png"));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void getPos(){
        xPos = 0;
        yPos = 10;
    }

    public void getSizes(){
        width = panel.tileSize*8;
        height = panel.tileSize*5;
    }

    public void update(){
        
        System.out.println("Receiving...");
        DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
        try {
           serverSocket.receive(receivePacket);
        } catch (IOException e) {
           e.printStackTrace();
        }
        sentence = new String(receivePacket.getData());
        System.out.println(sentence);
        getJSONString();
    }

    public void paintComponent(Graphics g){
            super.paintComponent(g);
            Graphics2D g2 = (Graphics2D)g;
            BufferedImage image = border;
            g2.setColor(Color.darkGray);
            g2.fillRect(0, 0, width, height);
            g2.drawImage(image, 0, 0, 400, 250, null);
            g2.setColor(Color.white);
            String str = "PLATOON DATA:";
            g2.drawString(str, xPos+30, yPos+20);
            g2.drawString(truckSpeed, xPos+30, yPos+40);
            g2.drawString(platoonSize, xPos+30, yPos+60);
            g2.drawString(safetyDistance, xPos+30, yPos+80);
    }

    @Override
    public void run() {
        double drawInterval = 1000000000/panel.FPS; //1 billion nanoseconds = 1 second / FPS is equal to how many times the drawing happens in one second
        double delta = 0; //accumulator
        long lastTime = System.nanoTime();
        long currentTime; 
    
        while (serverThread != null){

            currentTime = System.nanoTime();
            delta += (currentTime - lastTime)/drawInterval; //small integration of a frame optimization
            lastTime = currentTime;

            if (delta >= 1 ){
                update();
                repaint();
                delta--;
            }
        }
        
    }

    public void getJSONString(){
        JSONObject obj;
        try {
            obj = (JSONObject)parser.parse(sentence);
            JSONObject objBody = (JSONObject)obj.get("B");
            String objSpeed = (String)objBody.get("Speed");
            String objectSize = (String)objBody.get("PlatoonSize");
            System.out.println(objectSize);
            objSize = Integer.parseInt(objectSize);
            String objDistance = (String)objBody.get("SafetyDistance");
            truckSpeed = "Speed: "+objSpeed;
            System.out.println(truckSpeed);
            platoonSize = "Platoon Size: "+objectSize;
            System.out.println(platoonSize);
            safetyDistance = "Safety Distance: "+objDistance;
            System.out.println(safetyDistance);
        } catch (org.json.simple.parser.ParseException e) {
            
            e.printStackTrace();
        }
           
        
    }

    
}
