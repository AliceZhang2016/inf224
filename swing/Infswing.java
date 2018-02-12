import javax.swing.*;

import java.awt.BorderLayout;
import java.awt.event.*;
import java.io.*;
import java.net.*;

public class Infswing extends JFrame{
	private static final long serialVersionUID = 1L;
	static final String DEFAULT_HOST = "localhost";
	static final int DEFAULT_PORT = 3331;
	private int numRow = 30;
	private int numColumn = 60;
	JButton button1, button2, close, barBtn1, barBtn2, barClose;
	JTextArea textArea = new JTextArea(numRow,numColumn);
	JMenuBar menuBar;
	JMenu menu;
	JToolBar toolBar;
	JTextField barTF;
	Socket sock;
	private BufferedReader input;
	private BufferedWriter output;
	
	public static void main(String argv[]){
		String host = DEFAULT_HOST;
	    int port = DEFAULT_PORT;
	    if (argv.length >=1) host = argv[0];
	    if (argv.length >=2) port = Integer.parseInt(argv[1]);
	    
	    Infswing frame = null;
	    
	    try {
	    	frame = new Infswing(host, port);
	    	frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
			frame.pack();
			frame.setVisible(true);
	    }
	    catch (Exception e) {
	      System.err.println("Client: Couldn't connect to "+host+":"+port);
	      System.exit(1);
	    }
	    
	    System.out.println("Client connected to "+host+":"+port);
	}
	
	public Infswing(String host, int port) throws UnknownHostException,IOException{
		/* Ex 1
		JPanel jp = new JPanel();
		jp.add(button1 = new JButton("Print"));
		jp.add(button2 = new JButton("Play"));
		jp.add(close = new JButton("Close"));
		add(jp, BorderLayout.SOUTH);
		
		button1.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				textArea.setText("PRINT");
			}
		});
		
		button2.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				textArea.setText("PLAY");
			}
		});
		
		close.addActionListener(new CloseListener());
		*/
		
		JScrollPane scrollP = new JScrollPane(textArea);
		add(scrollP, BorderLayout.CENTER);
		
		menuBar = new JMenuBar();
		menu = new JMenu("Command...");
		JMenuItem item1, item2;
		
		Action addText1 = new SetContext("chercher", "chercher");
		Action addText2 = new SetContext("jouer", "jouer");
		item1 = new JMenuItem(addText1);
		item2 = new JMenuItem(addText2);
		menu.add(item1);
		menu.add(item2);
		menuBar.add(menu);
		setJMenuBar(menuBar);
		
		toolBar = new JToolBar();
		barBtn1 = new JButton("chercher");
		barBtn2 = new JButton("jouer");
		barClose = new JButton("fermer");
		barTF = new JTextField("Entrer un nom d'un media");
		barTF.setColumns(20);
		barBtn1.setAction(addText1);
		barBtn2.setAction(addText2);
		barClose.addActionListener(new CloseListener());
		toolBar.add(barBtn1);
		toolBar.add(barBtn2);
		toolBar.add(barClose);
		toolBar.add(barTF);
		
		add(toolBar, BorderLayout.NORTH);
		
		JPanel jp = new JPanel();
		button1 = new JButton("chercher");
		button1.setAction(addText1);
		button2 = new JButton("jouer");
		button2.setAction(addText2);
		close = new JButton("fermer");
		close.addActionListener(new CloseListener());
		jp.add(button1);
		jp.add(button2);
		jp.add(close);
		add(jp, BorderLayout.SOUTH);
		
		
		//network
		try {
			sock = new java.net.Socket(host,port);
		}
		catch(java.net.UnknownHostException e) {
			System.err.println("Client: Couldn't find host " + host + ":" + port);
			throw e;
		}
		catch(java.io.IOException e) {
			System.err.println("Client: Couldn't reach host " + host + ":" + port);
			throw e;
		}

		try {
			input = new BufferedReader(new InputStreamReader(sock.getInputStream()));
			output = new BufferedWriter(new OutputStreamWriter(sock.getOutputStream()));
		}
		catch(java.io.IOException e) {
			System.err.println("Client: Couldn't open input or output streams");
			throw e;
		}
	}
	
	public String send(String request) {
	    // Envoyer la requete au serveur
	    try {
	    	request += "\n";  // ajouter le separateur de lignes
	    	output.write(request, 0, request.length());
	    	output.flush();
	    }
	    catch (java.io.IOException e) {
	    	System.err.println("Client: Couldn't send message: " + e);
	    	return null;
	    }
	    
	    // Recuperer le resultat envoye par le serveur
	    try {
	    	return input.readLine();
	    }
	    catch (java.io.IOException e) {
	    	System.err.println("Client: Couldn't receive message: " + e);
	    	return null;
	    }
	}
	
	class CloseListener implements ActionListener{
		public void actionPerformed(ActionEvent e){
			System.exit(0);
		}
	}
	
	class SetContext extends AbstractAction{
		private static final long serialVersionUID = 1L;
		
		private String text;
		public SetContext(String _text, String s){
			super(_text);
			text = s;
		}
		
		public void actionPerformed(ActionEvent e){
			//textArea.setText(text);  //Ex2
			String request,response;
			String name = barTF.getText();
			if (name.length() == 0){
				JFrame diag = new JFrame("Error");
				JOptionPane.showMessageDialog(diag, "Please enter a name of multiMedia.");
			}else{
				request = text + " " + name;
				response = send(request);
				textArea.append(response);
				textArea.append("\n");
			}
		}
	}
}
