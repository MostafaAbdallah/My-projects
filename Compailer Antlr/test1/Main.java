// import ANTLR's runtime libraries
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.FileInputStream;
import java.io.InputStream;

public class Main {

	public static void main(String[] args) throws Exception {

		 String inputFile = null; 
        
        if ( args.length>0 )
        	 inputFile = args[0];
        
        InputStream is = System.in;
        
        if ( inputFile!=null ) 
        	is = new FileInputStream(inputFile);
		// create a CharStream that reads from standard input
		ANTLRInputStream input = new ANTLRInputStream(is);	
		// create a lexer that feeds off of input CharStream
		FirstSysLexer lexer = new FirstSysLexer(input);
		// create a buffer of tokens pulled from the lexer
		CommonTokenStream tokens = new CommonTokenStream(lexer);
		// create a parser that feeds off the tokens buffer
		
		FirstSysParser parser = new FirstSysParser(tokens);
		
		ParseTree tree = parser.prog(); // begin parsing at init rule
		
		//System.out.println(tree.toStringTree(parser)); // print LISP-style tree

		ParseTreeWalker walker = new ParseTreeWalker();
		// Walk the tree created during the parse, trigger callbacks
		walker.walk(new Lsystem(), tree);
		System.out.println(); // print a \n after translation
	}
}