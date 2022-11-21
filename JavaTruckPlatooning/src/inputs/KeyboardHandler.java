package src.inputs;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;


    
public class KeyboardHandler implements KeyListener{

    public boolean A_Pressed, D_Pressed = false;
    public boolean one_pressed, two_pressed, three_pressed, four_pressed, five_pressed = false;

    @Override
    public void keyTyped(KeyEvent e) {
        
    }

    @Override
    public void keyPressed(KeyEvent e) {

        int code = e.getKeyCode();

        if(code == KeyEvent.VK_A)
            A_Pressed = true;
        
        if(code == KeyEvent.VK_D)
            D_Pressed = true;

        if(code == KeyEvent.VK_1)
            one_pressed = true;
        if(code == KeyEvent.VK_2)
            two_pressed = true;
        if(code == KeyEvent.VK_3)
            three_pressed = true;
        if(code == KeyEvent.VK_4)
            four_pressed = true;
        if(code == KeyEvent.VK_5)
            five_pressed = true;

        
    }

    @Override
    public void keyReleased(KeyEvent e) {
        int code = e.getKeyCode();

        if(code == KeyEvent.VK_A)
            A_Pressed = false;
        
        if(code == KeyEvent.VK_D)
            D_Pressed = false;
        
    }
}
