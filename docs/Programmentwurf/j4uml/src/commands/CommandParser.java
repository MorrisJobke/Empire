package commands;

import java.io.File;

public class CommandParser {
	
	public CommandParser(String input) {
		String[] inputSplit = input.split(" ");
		int length = inputSplit.length;
		
		switch(inputSplit[0]){
			case "add": 
				if (length == 3)
					new AddCommand(inputSplit[1], inputSplit[2]);
				else
					System.out.println("error");
				break;
			
			case "del": 
				if (length == 2)
					new RemoveCommand(inputSplit[1]);
				else
					System.out.println("error");
				break;
				
			case "create":
				if (length == 1)
					new CreateCommand();
				break;
			//...
		}
	}
	
}
