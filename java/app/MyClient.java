import java.net.*;  
import java.io.*;  

class MyClient{

	Socket s;
	DataInputStream dataIn;  
	DataOutputStream dataOut;
	BufferedReader br;

	public MyClient()throws Exception{  
		s=new Socket("localhost",3333);  
		dataIn=new DataInputStream(s.getInputStream());  	
 		dataOut=new DataOutputStream(s.getOutputStream());  
		br =new BufferedReader(new InputStreamReader(System.in));  
		  
	}

	public void Send(String message) throws IOException{
		dataOut.writeUTF(message);  
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
