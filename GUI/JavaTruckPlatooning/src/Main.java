package src;

//import javax.swing.ImageIcon;
import javax.swing.JFrame;

public class Main{
    public static void main(String[] args){
        JFrame window = new JFrame();
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setResizable(false);
        window.setTitle("Les Trucks Hermanos");

        Panel panel = new Panel();
        window.add(panel);

        window.pack();

        window.setLocationRelativeTo(null);
        window.setVisible(true);

        panel.startThread();
    }
}
