package com.redpine.tradeClient;

import java.awt.Color;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Iterator;
import java.util.concurrent.ArrayBlockingQueue;

import javax.swing.BorderFactory;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JPanel;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.plot.XYPlot;
import org.jfree.data.Range;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

import com.redpine.TradeMessageConsumer.L1Data;
import com.redpine.TradeMessageConsumer.L1DataObserver;
import com.redpine.TradeMessageConsumer.TradeMessageConsumer;

/**
 * @author dbrown
 *
 */
public class TickData extends JFrame implements ActionListener, L1DataObserver
{
    /**
     * 
     */
    private static final long serialVersionUID = 1L;

    /**
     * 
     */
    private final ArrayBlockingQueue<Double> queue;

    /**
     * 
     */
    private final static int maxQueueSize = 1000;

    /**
     * 
     */
    private static String symbol;

    /**
     * 
     */
    private static JFreeChart chart = null;
    
    /**
     * 
     */
    public TickData()
    {
    	super("Tick Data");
	
    	queue = new ArrayBlockingQueue<Double>(maxQueueSize);

    	final GridBagConstraints constraint = new GridBagConstraints();
    	getContentPane().setLayout(new GridBagLayout());
	
    	String[] symbols = Configuration.getInstance().getSymbols();
        JComboBox<String> symbolList = new JComboBox<String>(symbols);
        symbolList.setSelectedIndex(0);
        symbolList.addActionListener(this);
        symbolList.setSize(100, 100);

        JPanel pane = new JPanel(); //use default FlowLayout
        pane.setBorder(BorderFactory.createEmptyBorder(5,5,5,5));
        pane.add(symbolList);
        
        constraint.fill = GridBagConstraints.HORIZONTAL;
        constraint.gridx = 0;
        constraint.gridy = 0;

        //Lay out the demo.
        add(pane, constraint);

        ChartPanel chartPanel = (ChartPanel) createDemoPanel();
        chartPanel.setPreferredSize(new java.awt.Dimension(1900, 500));
        constraint.fill = GridBagConstraints.CENTER;
        constraint.gridx = 0;
        constraint.gridy = 1;

        add(chartPanel, constraint);

        
        // Display the window.
        pack();
        setVisible(true);
    }
    
    /** Listens to the combo box. */
    public void actionPerformed(ActionEvent e) 
    {
        JComboBox cb = (JComboBox)e.getSource();
        symbol = (String)cb.getSelectedItem();
        this.setTitle("Tick Data: " + symbol);
        queue.clear();
   }
    
    private XYSeriesCollection createDataset() 
    {
	XYSeries s1 = new XYSeries("Price/Time");
	int i = 0;
	for(Iterator<Double> iter = queue.iterator(); iter.hasNext(); ++i)
	{
	    s1.add(i,iter.next());
	}
  
        XYSeriesCollection dataset = new XYSeriesCollection();
        dataset.addSeries(s1);

        return dataset;
    }

    public JPanel createDemoPanel() 
    {
        chart = createChart(createDataset());

        ChartPanel panel = new ChartPanel(chart);
 //       panel.setFillZoomRectangle(true);
 //       panel.setMouseWheelEnabled(true);
        TradeMessageConsumer.getInstance().observe(this);
        return panel;
    }
    
    public void update(L1Data data)
    {
	if(data.symbol_.equals(symbol))
	{
	    if(queue.size() >= maxQueueSize)
	    {
		queue.remove();
	    }
	    queue.add(new Double(data.price_));
	    XYPlot plot = chart.getXYPlot();
	    XYSeriesCollection dataCollection = createDataset();
	    double min = dataCollection.getRangeLowerBound(false);
	    double max = dataCollection.getRangeUpperBound(false);
	    plot.setDataset(dataCollection);
            plot.getRangeAxis().setRange(new Range(min - .00005, max + .00005));
	}
    }

    private JFreeChart createChart(XYSeriesCollection dataset) 
    {

        //         Generate the graph
     JFreeChart chart = ChartFactory.createXYLineChart("Tick Data Chart", // Title
                "", // x-axis Label
                "Price", // y-axis Label
                dataset, // Dataset
                PlotOrientation.VERTICAL, // Plot Orientation
                false, // Show Legend
                false, // Use tooltips
                false); // Configure chart to generate URLs?
    
         chart.setBackgroundPaint(Color.white);

	 XYPlot plot = chart.getXYPlot();

	 plot.setBackgroundPaint(Color.black);
	 plot.setDomainGridlinePaint(Color.white);
	 plot.setRangeGridlinePaint(Color.white);
	

        return chart;
    }
}
