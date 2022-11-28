package src.entities;
/*********IMPORTS********** */
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.IOException;

import javax.imageio.ImageIO;

import src.Panel;
import src.inputs.KeyboardHandler;

/* CLASS TRUCK */
/* Defined with X pos, Y pos, shift is the increment in the X-axis to spawn them at a different location from the initial pos */
/* an image buffer and a color */
public class Truck {

    public int x = 0; // X-Axis pos
    public int y = 0; // Y-Axis pos
    public int yOffset = 225;
    public int shift = 0; // Shift in the X-Axis
    public boolean spawnTruck = false; //Not sure yet how to use this but can be useful
    public BufferedImage red1, red2, blue1, blue2, green1, green2, pink1, pink2; //variable to store the buffered images of the trucks
    public String color; //arbitrary color of the truck, chosen randomly by the system
    public int imageCounter = 0; //variables used for animations
    public int imageNum = 1;
    public int speed = 3;
    public int id_truck;
    //public boolean isLeader = false;
    
    
    Panel panel;
    KeyboardHandler keyH;

    public Truck(Panel panel, KeyboardHandler keyH, int shift, String color){

        this.panel = panel;
        this.keyH = keyH;
        this.shift = shift;
        this.color = color;

        setValues(shift);
        getTruck();
    }

    public void moveToX(int shift){
        if(x >= shift)
            x -= speed;
    }

    //public void checkLeader(int id){
    //    if(id == 0)
    //        isLeader = true;
    //    else isLeader = false;
    //}

    public void setValues(int shift){
        x = (panel.screenWidth)+(panel.tileSize*2);   //Setting initial position values for each truck generated
        y = (panel.screenHeight/2)+yOffset;
    }

    public void getTruck(){
        //Storing and preparing images for the buffer
        try {
            red1 = ImageIO.read(getClass().getResourceAsStream("/src/res/trucks/TruckRed1.png"));
            red2 = ImageIO.read(getClass().getResourceAsStream("/src/res/trucks/TruckRed2.png"));
            blue1 = ImageIO.read(getClass().getResourceAsStream("/src/res/trucks/TruckBlue1.png"));
            blue2 = ImageIO.read(getClass().getResourceAsStream("/src/res/trucks/TruckBlue2.png"));
            green1 = ImageIO.read(getClass().getResourceAsStream("/src/res/trucks/TruckGreen1.png"));
            green2 = ImageIO.read(getClass().getResourceAsStream("/src/res/trucks/TruckGreen2.png"));
            pink1 = ImageIO.read(getClass().getResourceAsStream("/src/res/trucks/TruckPink1.png"));
            pink2 = ImageIO.read(getClass().getResourceAsStream("/src/res/trucks/TruckPink2.png"));

        } catch(IOException e){
            e.printStackTrace();
        }
    }
    public void getID(int id){
        id_truck = id;
    }

    public void update(int id) {
        //Calling the update functionality for the thread
        //checkLeader(id);
        getID(id);
        imageCounter++;
        if(imageCounter > 10){
            if(imageNum == 1){
                imageNum = 2;
            } else if(imageNum == 2) {
                imageNum = 1;
            }   
            imageCounter = 0;
        }
        moveToX(shift);

    }

    public void draw(Graphics2D g2) {
        //Drawing the trucks according to the stored images
        BufferedImage image = null;

        switch(color){
            case "red":
                if(imageNum == 1)
                    image = red1;
                if(imageNum == 2)
                    image = red2;
                break;

            case "blue":
                if(imageNum == 1)
                    image = blue1;
                if(imageNum == 2)
                    image = blue2;
                break;

            case "green":
                if(imageNum == 1)
                    image = green1;
                if(imageNum == 2)
                    image = green2;
                break;

            case "pink":
                if(imageNum == 1)
                    image = pink1;
                if(imageNum == 2)
                    image = pink2;
                break;
        }
        g2.drawImage(image, x, y, panel.tileSize*4, panel.tileSize*2, null);
        if(id_truck == 0)
            g2.drawString("LEADER ID: "+id_truck, x+10, y);
        else g2.drawString("ID: "+id_truck, x+panel.tileSize, y);

    }
}
