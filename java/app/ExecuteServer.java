import java.net.*;  
import java.io.*; 

class MyServer extends Thread {

	 ServerSocket ss;
	 Socket s[];
	 DataInputStream dataIn[];
	 DataOutputStream dataOut[];
	 int count;
	 String users[];
	 String userMessages[];

	public void run() {
		int id = count;
		count++;
		try{
			s[id]=ss.accept();
			dataIn[id]=new DataInputStream(s[id].getInputStream());  
			dataOut[id]=new DataOutputStream(s[id].getOutputStream());  
			BufferedReader br=new BufferedReader(new InputStreamReader(System.in));  
			String message="",responce="";  
			message=dataIn[id].readUTF();  
			String content[] = message.split("---");
			users[id] = content[0];
			System.out.println(content[0] + content[1]);
			while(!message.equals("bye")){  
				message=dataIn[id].readUTF();
				String content1[] = message.split("---");
				for (int I=0;I<count;I++){
					if (content1[0].equals("all")){
						userMessages[I] = userMessages[I]+content1[1];
					}else if(content1[0] == users[I]){
						userMessages[id] =  userMessages[id] + content1[1];
						userMessages[I] =  userMessages[I] + content1[1];
					}
					dataOut[I].writeUTF(userMessages[I]);
				}    
			}  
			dataIn[id].close();
		}catch (Exception e){
			System.out.println(e);
		}
		  
	}  


	MyServer() throws Exception{  
		ss = new ServerSocket(3333); 
		s = new Socket[10];
		dataIn = new DataInputStream [10];
		dataOut = new DataOutputStream [10];
		userMessages = new String[10];
		users = new String[10];
		count =0;
		for (int i = 0;i<10;i++){
			userMessages[i] = "";
		}   
	}
} 

class ExecuteServer{
	public static void main(String[] args) throws Exception{
		MyServer t[] = new MyServer[10];
		for (int i=0;i<10;i++){
			t[i] =   new MyServer();
			t[i].start();	
		}
	}
}