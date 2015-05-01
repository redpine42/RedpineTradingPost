package com.redpine.TradeClient;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.KeyStroke;

import com.redpine.TradeMessageConsumer.TradeMessageConsumer;

public class TradeClient implements ActionListener
{
    private  JFrame mainFrame;
    private  JMenuBar menuBar;
    private  JMenu menu;
    private  JMenuItem menuItem;

    public TradeClient()
    {
	createAndShowGUI();
	TradeMessageConsumer.getInstance().run();
    }
    
    private void createAndShowGUI()
    {
	// Create and set up the window.
	mainFrame = new JFrame("Trade Client");
	mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

	JLabel emptyLabel = new JLabel("");
	emptyLabel.setPreferredSize(new Dimension(2000, 1100));
	mainFrame.getContentPane().add(emptyLabel, BorderLayout.CENTER);

	// Create the menu bar.
	menuBar = new JMenuBar();

	// Build the first menu.
	menu = new JMenu("Settings");
	menu.setMnemonic(KeyEvent.VK_S);
	menu.getAccessibleContext().setAccessibleDescription(
		"Load and Save Display Settings");
	menuBar.add(menu);

	// a group of JMenuItems
	menuItem = new JMenuItem("Load Settings", KeyEvent.VK_L);
	menuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_L,
		ActionEvent.ALT_MASK));
	menuItem.getAccessibleContext().setAccessibleDescription(
		"Load Saved Settings");
	menuItem.setEnabled(false);
	menu.add(menuItem);

	menuItem = new JMenuItem("Save Settings", KeyEvent.VK_S);
	menuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S,
		ActionEvent.ALT_MASK));
	menuItem.getAccessibleContext().setAccessibleDescription(
		"Save Current Settings");
	menuItem.setEnabled(false);
	menu.add(menuItem);

	// Build second menu in the menu bar.
	menu = new JMenu("Components");
	menu.setMnemonic(KeyEvent.VK_C);
	menu.getAccessibleContext().setAccessibleDescription(
		"This menu creates componets");
	menuItem.setEnabled(false);
	menuBar.add(menu);

	menuItem = new JMenuItem("Bar Chart", KeyEvent.VK_B);

	menuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_B,
		ActionEvent.ALT_MASK));
	menuItem.getAccessibleContext().setAccessibleDescription(
		"Creates a bar Chart");
	menuItem.setEnabled(false);
	menu.add(menuItem);

	menuItem = new JMenuItem("Market Depth", KeyEvent.VK_M);

	menuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_M,
		ActionEvent.ALT_MASK));
	menuItem.getAccessibleContext().setAccessibleDescription(
		"Creates a Market Depth(L2) Window");
	menuItem.setEnabled(false);
	menu.add(menuItem);

	menuItem = new JMenuItem("Tick Data Chart", KeyEvent.VK_T);
	menuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_T,
		ActionEvent.ALT_MASK));
	menuItem.getAccessibleContext().setAccessibleDescription(
		"Creates a tick data chart");
	menuItem.setEnabled(true);
	menuItem.addActionListener(this);
	menu.add(menuItem);

	mainFrame.setJMenuBar(menuBar);

	// Display the window.
	mainFrame.pack();
	mainFrame.setVisible(true);
    }

    /**
     * @param args
     */
    public static void main(String[] args)
    {
	// Schedule a job for the event-dispatching thread:
	// creating and showing this application's GUI.
	javax.swing.SwingUtilities.invokeLater(new Runnable()
	{
	    public void run()
	    {
		new TradeClient();
	    }
	});
    }

    //@Override
    public void actionPerformed(ActionEvent e)
    {
	// TODO Auto-generated method stub
	JMenuItem source = (JMenuItem)(e.getSource());
	if(source.getText().equals("Tick Data Chart"))
	{
	    new TickData();
	}
    }
}
