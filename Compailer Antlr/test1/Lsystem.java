import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.util.*;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.io.FileNotFoundException;
import java.util.ArrayList;


public class Lsystem extends FirstSysBaseListener {

	private String axiom = "";
	private ArrayList <String> production = new ArrayList <String>();
	private float angle = 0.0f;
	private float lineLength  = 0.0f; 
	private ArrayList <String> id = new ArrayList <String>();
	private int iterations = 0;

	@Override
	public void enterProg(FirstSysParser.ProgContext ctx) {
		
	}
	
	@Override
	public void exitProg(FirstSysParser.ProgContext ctx) {
		
	}

	@Override
	public void enterAxiom(FirstSysParser.AxiomContext ctx) {
		//axiom = ctx.getText();
		List<FirstSysParser.LstrContext> list = ctx.lstr();

		for(int i = 0; i < list.size(); i++){
			axiom = axiom + list.get(i).getText();
			
		}
		System.out.println(axiom);
	}
	
	@Override
	public void exitAxiom(FirstSysParser.AxiomContext ctx) {
				
	}

	@Override
	public void enterProduction(FirstSysParser.ProductionContext ctx) {
		List<FirstSysParser.LstrContext> list = ctx.lstr();
		String str = "";
		for(int i = 0; i < list.size(); i++){
			
			str = str + list.get(i).getText();
			
		}
		production.add(str);
		System.out.println(str);
		id.add(ctx.ID().getText());
		System.out.println(ctx.ID().getText());

	}
	
	@Override
	public void exitProduction(FirstSysParser.ProductionContext ctx) {
		
	}
	@Override
	public void enterAngle(FirstSysParser.AngleContext ctx) {
		if(ctx.FLOAT() != null)
			angle = Float.valueOf(ctx.FLOAT().getText());
		else
			angle = Float.valueOf(ctx.INT().getText());
		System.out.println(angle);
	}
	
	@Override
	public void exitAngle(FirstSysParser.AngleContext ctx) { 
		
	}
	
	@Override
	public void enterLineLenght(FirstSysParser.LineLenghtContext ctx) {
		if(ctx.FLOAT() != null)
			lineLength = Float.valueOf(ctx.FLOAT().getText());
		else
			lineLength = Float.valueOf(ctx.INT().getText());
		System.out.println(lineLength);
	}
	
	@Override
	public void exitLineLenght(FirstSysParser.LineLenghtContext ctx) { 

	}

	@Override
	public void enterIteration(FirstSysParser.IterationContext ctx) {
		iterations = Integer.valueOf(ctx.INT().getText());
		System.out.println(iterations);
	}
	
	@Override
	public void exitIteration(FirstSysParser.IterationContext ctx){
		String producted = axiom;
		String temp = "";
		boolean found = false;
		for (int i = 0; i < iterations; i++) {
			
			for (int j = 0; j < producted.length(); j++) {
				found = false;
				for (int j2 = 0; j2 < id.size(); j2++) {
					
					if(producted.charAt(j) == id.get(j2).charAt(0)){
						temp = temp + production.get(j2);
						found = true;
						break;
					}
					
				}
				if(!found){
					temp = temp + producted.charAt(j);
				}
				
			}
			producted = temp;
			temp = "";
			
		}
		producted = angle + " " + lineLength + " " + producted;
		System.out.println(producted);
		PrintWriter writer;
		try {
			writer = new PrintWriter("the-Lsys.txt", "UTF-8");
			writer.println(producted);
			
			writer.close();

		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}
}