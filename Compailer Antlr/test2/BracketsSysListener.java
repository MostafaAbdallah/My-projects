// Generated from BracketsSys.g4 by ANTLR 4.5
import org.antlr.v4.runtime.misc.NotNull;
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link BracketsSysParser}.
 */
public interface BracketsSysListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link BracketsSysParser#prog}.
	 * @param ctx the parse tree
	 */
	void enterProg(BracketsSysParser.ProgContext ctx);
	/**
	 * Exit a parse tree produced by {@link BracketsSysParser#prog}.
	 * @param ctx the parse tree
	 */
	void exitProg(BracketsSysParser.ProgContext ctx);
	/**
	 * Enter a parse tree produced by {@link BracketsSysParser#axiom}.
	 * @param ctx the parse tree
	 */
	void enterAxiom(BracketsSysParser.AxiomContext ctx);
	/**
	 * Exit a parse tree produced by {@link BracketsSysParser#axiom}.
	 * @param ctx the parse tree
	 */
	void exitAxiom(BracketsSysParser.AxiomContext ctx);
	/**
	 * Enter a parse tree produced by {@link BracketsSysParser#lstr}.
	 * @param ctx the parse tree
	 */
	void enterLstr(BracketsSysParser.LstrContext ctx);
	/**
	 * Exit a parse tree produced by {@link BracketsSysParser#lstr}.
	 * @param ctx the parse tree
	 */
	void exitLstr(BracketsSysParser.LstrContext ctx);
	/**
	 * Enter a parse tree produced by {@link BracketsSysParser#production}.
	 * @param ctx the parse tree
	 */
	void enterProduction(BracketsSysParser.ProductionContext ctx);
	/**
	 * Exit a parse tree produced by {@link BracketsSysParser#production}.
	 * @param ctx the parse tree
	 */
	void exitProduction(BracketsSysParser.ProductionContext ctx);
	/**
	 * Enter a parse tree produced by {@link BracketsSysParser#angle}.
	 * @param ctx the parse tree
	 */
	void enterAngle(BracketsSysParser.AngleContext ctx);
	/**
	 * Exit a parse tree produced by {@link BracketsSysParser#angle}.
	 * @param ctx the parse tree
	 */
	void exitAngle(BracketsSysParser.AngleContext ctx);
	/**
	 * Enter a parse tree produced by {@link BracketsSysParser#lineLenght}.
	 * @param ctx the parse tree
	 */
	void enterLineLenght(BracketsSysParser.LineLenghtContext ctx);
	/**
	 * Exit a parse tree produced by {@link BracketsSysParser#lineLenght}.
	 * @param ctx the parse tree
	 */
	void exitLineLenght(BracketsSysParser.LineLenghtContext ctx);
	/**
	 * Enter a parse tree produced by {@link BracketsSysParser#iteration}.
	 * @param ctx the parse tree
	 */
	void enterIteration(BracketsSysParser.IterationContext ctx);
	/**
	 * Exit a parse tree produced by {@link BracketsSysParser#iteration}.
	 * @param ctx the parse tree
	 */
	void exitIteration(BracketsSysParser.IterationContext ctx);
}