import java.applet.*;  
import javax.swing.*;  
import java.awt.event.*;
import MyClient.*;

public class EventJApplet extends JApplet implements ActionListener{  
    JButton b;  
    JTextField tf; 
    MyClient hi; 
 
    public void init(){  
	    
	    tf=new JTextField();  
	    tf.setBounds(30,40,150,20);  
	      
	    b=new JButton("Click");  
	    b.setBounds(80,150,70,40);  
	      
	    add(b);add(tf);  
	    b.addActionListener(this);  
	      
	    setLayout(null);  
    }  
      
    public void actionPerformed(ActionEvent e){  
		try{
			hi = new MyClient();
			hi.login("saravanan","hi");
			hi.send("hi","all");			
	    }catch (Exception ei){
	    	System.out.println(ei);
    	}  
	}
}  
