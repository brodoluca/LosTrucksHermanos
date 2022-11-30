package src;

//import java.net.DatagramSocket;

//import javax.swing.ImageIcon;
import javax.swing.JFrame;

import src.entities.Console;

public class Main{
    public static void main(String[] args) throws Exception{

        //DatagramSocket serverSocket = new DatagramSocket(9876);
        //byte[] receiveData = new byte[2048];

        JFrame window = new JFrame();
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setResizable(false);
        window.setTitle("Les Trucks Hermanos");

        
        Panel panel = new Panel();
        Console console = new Console(panel);
        
        //UDPServer udpServer = new UDPServer(serverSocket, receiveData);
        window.add(panel);

        window.pack();

        window.setLocationRelativeTo(null);
        window.setVisible(true);

        
        panel.startThread();
        console.startThread();
        
    }
}
