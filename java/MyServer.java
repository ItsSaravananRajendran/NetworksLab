import java.net.*;  
import java.io.*; 

class MyServer{  
	public static void main(String args[])throws Exception{  
		ServerSocket ss=new ServerSocket(3333);  
		Socket s=ss.accept();  
		DataInputStream dataIn=new DataInputStream(s.getInputStream());  
		DataOutputStream dataOut=new DataOutputStream(s.getOutputStream());  
		BufferedReader br=new BufferedReader(new InputStreamReader(System.in));  
		  
		String message="",responce="";  
		while(!message.equals("bye")){  
			message=dataIn.readUTF();  
			System.out.println("client says: "+message);  
			responce=br.readLine();  
			dataOut.writeUTF(responce);  
			dataOut.flush();  
		}  
		dataIn.close();  
		s.close();  
		ss.close();  
	}
} 