package src.entities;
/*********IMPORTS********** */
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.IOException;

import javax.imageio.ImageIO;

import src.Panel;
//import src.inputs.KeyboardHandler;

/* CLASS TRUCK */
/* Defined with X pos, Y pos, shift is the increment in the X-axis to spawn them at a different location from the initial pos */
/* an image buffer and a color */
public class Cloud {

    public int x = 0; // X-Axis pos
    public int y = 0; // Y-Axis pos
    public int yOffset = 225;
    public int shift = 0; // Shift in the X-Axis
    public BufferedImage cloud1, cloud2, cloud3; //variable to store the buffered images of the trucks
    public int speed = 3;
    public int num = 0;
    
    
    Panel panel;

    public Cloud(Panel panel, int shift, int num){

        this.panel = panel;
        this.shift = shift;
        this.num = num;

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
        y = (panel.screenHeight)+yOffset;
    }

    public void getTruck(){
        //Storing and preparing images for the buffer
        try {
            cloud1 = ImageIO.read(getClass().getResourceAsStream("/src/res/clouds/Cloud1.png"));
            cloud2 = ImageIO.read(getClass().getResourceAsStream("/src/res/clouds/Cloud2.png"));
            cloud3 = ImageIO.read(getClass().getResourceAsStream("/src/res/clouds/Cloud3.png"));

        } catch(IOException e){
            e.printStackTrace();
        }
    }

    public void update(int id) {
        //Calling the update functionality for the thread
        //checkLeader(id);
        moveToX(shift);

    }

    public void draw(Graphics2D g2) {
        //Drawing the trucks according to the stored images
        BufferedImage image = null;
        
        switch(num){
            case 1:
                image = cloud1;
                break;
            case 2:
                image = cloud2;
            case 3:
                image = cloud3;
        }

        g2.drawImage(image, x, y, panel.tileSize*4, panel.tileSize*2, null);

    }
}
