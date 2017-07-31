import java.net.*;  
import java.io.*;  

class MyClient{

	Socket s;
	DataInputStream dataIn;  
	DataOutputStream dataOut;
	BufferedReader br;
	String ClientId;
	String otherMsg[];

	public MyClient()throws Exception{  
		s=new Socket(InetAddress.getLocalHost(),15151);  
		dataIn=new DataInputStream(s.getInputStream());  	
 		dataOut=new DataOutputStream(s.getOutputStream());  
		br =new BufferedReader(new InputStreamReader(System.in)); 
		ClientId = "";
		  
	}

	public void login(String username,String password) throws IOException{
		ClientId = username;
		dataOut.writeUTF(username +"---"+password);
	}

	public void send(String message,String Receiver) throws IOException{
		dataOut.writeUTF(Receiver +"---"+ClientId+": "+message);  
		dataOut.flush();  
	}  

	public String receive() throws IOException{
		String responce=dataIn.readUTF();  
		return responce;
	}
				  
	public void close() throws IOException{
		dataIn.close();
		dataOut.close();  
		s.close();  
	}	
}  
