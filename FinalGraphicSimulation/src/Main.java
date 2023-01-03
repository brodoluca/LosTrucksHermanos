package src;

import javax.swing.JFrame;
import src.entities.Console;

public class Main{
    public static void main(String[] args) throws Exception{

        JFrame window = new JFrame();
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setResizable(false);
        window.setTitle("Les Trucks Hermanos");

        Panel panel = new Panel();
        Console console = new Console(panel);
        
        window.add(panel);
        panel.add(console);

        window.pack();

        window.setLocationRelativeTo(null);
        window.setVisible(true);
        console.setVisible(true);

        panel.startThread();
        console.startThread();
        
    }
}
