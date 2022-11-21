package src.entities;

import src.Panel;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;

import javax.imageio.ImageIO;

public class Console {

    int xPos = 0;
    int yPos = 0;
    int width = 0;
    int height = 0;
    int numTrucks = 0;
    int leaderID = 0;
    public BufferedImage border;

    Panel panel;
    

    public Console(Panel panel){
        this.panel = panel;
        getPos();
        getSize();
        getBorder();

    }

    public void getBorder(){
        try {
            border = ImageIO.read(getClass().getResourceAsStream("/src/res/border.png"));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void getPos(){
        xPos = 100;
        yPos = 50;
    }

    public void getSize(){
        width = panel.tileSize*8;
        height = panel.tileSize*5;
    }

    public void update(int id, int nTrucks){
        leaderID = id;
        numTrucks = nTrucks;
    }

    public void draw(Graphics2D g2){
        BufferedImage image = border;
        g2.setColor(Color.darkGray);
        g2.fillRect(xPos, yPos, width, height);
        g2.drawImage(image, xPos-10, yPos-10, 410, 260, null);
        g2.setColor(Color.white);
        String str = ("Number of trucks: "+numTrucks);
        String str2 = ("Leader ID: "+leaderID);
        g2.drawString(str, xPos+20, yPos+20);
        g2.drawString(str2, xPos+20, yPos+30);
    }
    
}
