package alt_commands;

import java.util.Vector;

public class CommandCollection {
	private Vector<BasicCommand> commands;
	
	
	public void registerCommand(BasicCommand command)
	{
		commands.add(command);
	}
	
	public void callCommand(Vector<String> args)
	{
		
	}
}
