import java.net.*;  
import java.io.*;  

class MyClient{  
	public static void main(String args[])throws Exception{  
		Socket s=new Socket("localhost",3333);  
		DataInputStream dataIn=new DataInputStream(s.getInputStream());  
		DataOutputStream dataOut=new DataOutputStream(s.getOutputStream());  
		BufferedReader br=new BufferedReader(new InputStreamReader(System.in));  
		  
		String message="",responce="";  
		while(!message.equals("bye")){  
			message=br.readLine();  
			dataOut.writeUTF(message);  
			dataOut.flush();  
			responce=dataIn.readUTF();  
			System.out.println("Server says: "+responce);  
		}  
		  
		dataOut.close();  
		s.close();  
	}
}  
