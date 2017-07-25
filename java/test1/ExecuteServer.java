import java.net.*;  
import java.io.*; 

class MyServer extends Thread {

	 static Socket s[];
	 static DataInputStream dataIn[];
	 static DataOutputStream dataOut[];
	 static int count;
	 static String users[];
	 static String userMessages[][];

	static { 
		s = new Socket[10];
		dataIn = new DataInputStream [10];
		dataOut =  new DataOutputStream [10];
		users = new String[10];
		userMessages = new String[10][10];
		count = 0;
		for (int j=0;j<10;j++){
			for (int i = 0;i<10;i++){
				userMessages[j][i] = "";
			}	
		}
	}

	public void run() {
		int id = count;
		count++;
		try{
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
						userMessages[id][I] = userMessages[id][I]+content1[1];
						if (id != I){
							userMessages[I][id] = userMessages[I][id]+content1[1];	
						}
					}else if(content1[0] == users[I]){
						userMessages[id][id] =  userMessages[id][id] + content1[1];
						userMessages[I][id] =  userMessages[I][id] + content1[1];
					}
					dataOut[I].writeUTF(userMessages[id][I]);
				}    
			}  
			dataIn[id].close();
		}catch (Exception e){
			System.out.println(e);
		}
		  
	}  


	MyServer(Socket ser) throws Exception{  
		s[count] = ser;
	}
} 

class ExecuteServer{
	
	static ServerSocket ss;
	static Socket socket = null; 

	public static void main(String[] args) throws Exception{
		try {
            		ss = new ServerSocket(15151);
        	} catch (IOException e) {
            		e.printStackTrace();
        	}
		while (true) {
		    try {
		        socket = ss.accept();
		    } catch (IOException e) {
		        System.out.println("I/O error: " + e);
		    }
		    // new thread for a client
		    new MyServer(socket).start();
		}
	}
}
