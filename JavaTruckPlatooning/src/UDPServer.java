package src;

import org.json.simple.JSONObject;
import org.json.simple.parser.ParseException;
import org.json.simple.parser.JSONParser;
import java.io.*;
import java.net.*;
 
public class UDPServer implements Runnable
{
   Thread serverThread;
   byte[] receiveData;
   DatagramSocket serverSocket;
   JSONParser parser = new JSONParser();
   public String sentence;
   public String objSpeed;
   public String objSize;
   public String objDistance;
   public String truckSpeed = "0";
   public String platoonSize = "0";
   public String safetyDistance = "0";

   public UDPServer(DatagramSocket serverSocket, byte[] receiveData) throws Exception
      {
         this.serverSocket = serverSocket;
         this.receiveData = receiveData;
         parser = new JSONParser();
      }

   public void startThread(){
      serverThread = new Thread(this);
      serverThread.start();
   }

   @Override
   public void run() {
      while(true){
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
         try {
            Thread.sleep(2000);
         } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
         }
      }
   }

   public void getJSONString(){
      try {
         JSONObject obj = (JSONObject)parser.parse(sentence);
         JSONObject objBody = (JSONObject)obj.get("B");
         objSpeed = (String)objBody.get("Speed");
         objSize = (String)objBody.get("PlatoonSize");
         objDistance = (String)objBody.get("SafetyDistance");
         truckSpeed = "Speed: "+objSpeed;
         System.out.println(truckSpeed);
         platoonSize = "Platoon Size: "+objSize;
         System.out.println(platoonSize);
         safetyDistance = "Safety Distance: "+objDistance;
         System.out.println(safetyDistance);


      } catch (ParseException e) {
         e.printStackTrace();
      }
   }
   
}