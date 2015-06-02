// Generated from FirstSys.g4 by ANTLR 4.5
import org.antlr.v4.runtime.misc.NotNull;
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link FirstSysParser}.
 */
public interface FirstSysListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link FirstSysParser#prog}.
	 * @param ctx the parse tree
	 */
	void enterProg(FirstSysParser.ProgContext ctx);
	/**
	 * Exit a parse tree produced by {@link FirstSysParser#prog}.
	 * @param ctx the parse tree
	 */
	void exitProg(FirstSysParser.ProgContext ctx);
	/**
	 * Enter a parse tree produced by {@link FirstSysParser#axiom}.
	 * @param ctx the parse tree
	 */
	void enterAxiom(FirstSysParser.AxiomContext ctx);
	/**
	 * Exit a parse tree produced by {@link FirstSysParser#axiom}.
	 * @param ctx the parse tree
	 */
	void exitAxiom(FirstSysParser.AxiomContext ctx);
	/**
	 * Enter a parse tree produced by {@link FirstSysParser#lstr}.
	 * @param ctx the parse tree
	 */
	void enterLstr(FirstSysParser.LstrContext ctx);
	/**
	 * Exit a parse tree produced by {@link FirstSysParser#lstr}.
	 * @param ctx the parse tree
	 */
	void exitLstr(FirstSysParser.LstrContext ctx);
	/**
	 * Enter a parse tree produced by {@link FirstSysParser#production}.
	 * @param ctx the parse tree
	 */
	void enterProduction(FirstSysParser.ProductionContext ctx);
	/**
	 * Exit a parse tree produced by {@link FirstSysParser#production}.
	 * @param ctx the parse tree
	 */
	void exitProduction(FirstSysParser.ProductionContext ctx);
	/**
	 * Enter a parse tree produced by {@link FirstSysParser#angle}.
	 * @param ctx the parse tree
	 */
	void enterAngle(FirstSysParser.AngleContext ctx);
	/**
	 * Exit a parse tree produced by {@link FirstSysParser#angle}.
	 * @param ctx the parse tree
	 */
	void exitAngle(FirstSysParser.AngleContext ctx);
	/**
	 * Enter a parse tree produced by {@link FirstSysParser#lineLenght}.
	 * @param ctx the parse tree
	 */
	void enterLineLenght(FirstSysParser.LineLenghtContext ctx);
	/**
	 * Exit a parse tree produced by {@link FirstSysParser#lineLenght}.
	 * @param ctx the parse tree
	 */
	void exitLineLenght(FirstSysParser.LineLenghtContext ctx);
	/**
	 * Enter a parse tree produced by {@link FirstSysParser#iteration}.
	 * @param ctx the parse tree
	 */
	void enterIteration(FirstSysParser.IterationContext ctx);
	/**
	 * Exit a parse tree produced by {@link FirstSysParser#iteration}.
	 * @param ctx the parse tree
	 */
	void exitIteration(FirstSysParser.IterationContext ctx);
}