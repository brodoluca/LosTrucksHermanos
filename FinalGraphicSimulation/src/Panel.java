package src;

import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.util.ArrayList;
import java.util.concurrent.ThreadLocalRandom;
import java.awt.Image;
import src.entities.Console;

import javax.swing.ImageIcon;
import javax.swing.JPanel;
import src.entities.Truck;
//import src.inputs.KeyboardHandler;

public class Panel extends JPanel implements Runnable{

    private Image img;

    final int defaultTileSize = 10;
    final int scale = 5;
    
    public final int tileSize = defaultTileSize * scale; //50 pixel
    
    final int maxScreenCol = 30;
    final int maxScreenRow = 15;

    public final int screenWidth = tileSize * maxScreenCol; //1500 pixel
    public final int screenHeight = tileSize * maxScreenRow; //750 pixel

    public int FPS = 100;
    public static int increment = 0;
    int count = 1;
    String[] color = {"red","blue","green","pink"};
    int xBackGround = 0;
    int yBackGround = 0;
    int speed = 1;
    int xOffset = 1000;
    int leader_id;

    //Console console = new Console(this);
    //KeyboardHandler keyH = new KeyboardHandler();
    
    Thread mainThread;
    ArrayList<Truck> trucks = new ArrayList<Truck>();
    ArrayList<String> messages = new ArrayList<String>();

    public Panel(){
        
        img = new ImageIcon("src/res/background.png").getImage();
        this.setPreferredSize(new Dimension(screenWidth, screenHeight));
        this.setDoubleBuffered(true);
        //this.addKeyListener(keyH);
        this.setFocusable(true);
    }

    public void startThread(){
        mainThread = new Thread(this);
        mainThread.start();
    }

    @Override
    public void run() {

        double drawInterval = 1000000000/FPS; //1 billion nanoseconds = 1 second / FPS is equal to how many times the drawing happens in one second
        double delta = 0; //accumulator
        long lastTime = System.nanoTime();
        long currentTime; 
    
        while (mainThread != null){

            currentTime = System.nanoTime();
            delta += (currentTime - lastTime)/drawInterval; //small integration of a frame optimization
            lastTime = currentTime;

            if (delta >= 1 ){
                update();   // update and repaint are called FPS times in one second in order to update the screen with 
                repaint();  // the new information
                delta--;
            }
        }
    }

    public static <T> T getRandomElement(T[] arr){
        return arr[ThreadLocalRandom.current().nextInt(arr.length)];
    }

    public String getRandColor(){
        String randColor = getRandomElement(color);
        return randColor;
    }

    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2 = (Graphics2D)g;
        
        g2.drawImage(img, xBackGround-1500, 0, screenWidth, screenHeight, null);
        if(xBackGround == 0)
            xOffset = 1500;
        if(xBackGround == 1500)
            xBackGround = 0;
        if(xBackGround > 0){
            g2.drawImage(img, xBackGround, 0, screenWidth, screenHeight, null);
        }
            
        for (int i=0; i<trucks.size(); i++)
            trucks.get(i).draw(g2);
    }

    public void update() {
        //A pressed is a user input which has to be replaced with the actual "addTruck()" function in the main program
        xBackGround += speed;
        xOffset += speed;

        if(count == Console.objSize && Console.objSize > 0){
            String randColor = getRandColor();
            trucks.add(new Truck(this, increment, randColor));
            increment += 200;
            count++;
            }

        while(Console.objSize < trucks.size()){
            trucks.remove(trucks.size() - 1);
            count--;
            increment -= 200;
        }
        for (int i=0; i<trucks.size(); i++){
            if(i == 0){
                leader_id = 0;
            }
            trucks.get(i).update(i);
        }
    }
        
       
}

    

