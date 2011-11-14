package alt_commands;

import java.util.Vector;

public abstract class BasicCommand {

	protected String syntax;
	protected int argCount;
	protected Vector<String> args;
	
	protected BasicCommand(Vector<String> args)
	{
		this.args = args;
		exec();
	}
	
	abstract void exec();
	
}
