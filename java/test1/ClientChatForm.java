import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.print.PrinterException;
import java.awt.Frame;
import java.awt.Color;
import java.io.*;
import java.io.IOException;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.sql.Time;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import MyClient.*;

public class ClientChatForm extends JFrame implements ActionListener {
	static Socket conn;
	JPanel panel;
	JTextField NewMsg;
	JTextArea ChatHistory;
	JButton Send;
	static MyClient me ;

	static{
		try{
			me = new MyClient();	
		}
		catch( Exception e){
			System.out.println(e);
		}
	}

	public ClientChatForm() throws UnknownHostException, IOException {
		panel = new JPanel();
		NewMsg = new JTextField();
		ChatHistory = new JTextArea();
		Send = new JButton("Send");
		this.setSize(500, 500);
		
		this.setVisible(true);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		panel.setLayout(null);
		this.add(panel);
		ChatHistory.setBounds(20, 20, 450, 360);
		panel.add(ChatHistory);
		setBackground(new Color(192, 192, 192));
		NewMsg.setBounds(20, 400, 340, 30);
		panel.add(NewMsg);
		Send.setBounds(375, 400, 95, 30);
		panel.add(Send);
		Send.addActionListener(this);
		//conn = new Socket(InetAddress.getLocalHost(), 15151);
		me.login("saro1","hi");

		/*
		 * for remote pc use ip address of server with function
		 * InetAddress.getByName("Provide ip here")
		 * ChatHistory.setText("Connected to Server");
		 */

		ChatHistory.setText("Connected to Server\n");
		this.setTitle("Client");
		while (true) {
			try {   
				String string = me.receive();
				ChatHistory.setText(ChatHistory.getText() + 'n' + "\nServer:"
						+ string);
				FileOutputStream f = new FileOutputStream("chat.txt");
				String t = ChatHistory.getText()+ string;
				byte [] co = t.getBytes();				
				f.write(co);
				f.close();
				
			} catch (Exception e1) {
				ChatHistory.setText(ChatHistory.getText() + 'n'
						+ "Message sending fail:Network Error");
				try {
					Thread.sleep(300000);
					System.exit(0);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		if ((e.getSource() == Send) && (NewMsg.getText() != "")) {

			ChatHistory.setText(ChatHistory.getText() + 'n' + "\nME:"
					+ NewMsg.getText());
			try {
				me.send(NewMsg.getText(),"saro");
			} catch (Exception e1) {
				ChatHistory.setText(ChatHistory.getText() + 'n'
						+ "\nMessage sending fail:Network Error");
				try {
					Thread.sleep(300000);
					System.exit(0);
				} catch (InterruptedException e2) {
					// TODO Auto-generated catch block
					e2.printStackTrace();
				}
			}
			NewMsg.setText("");
		}
	}

	public static void main(String[] args) throws UnknownHostException,
			IOException {
		ClientChatForm chatForm = new ClientChatForm();
	}
}
