package dataTypes;

abstract public class Property<Type> {

	/**
	 * @uml.property  name="key"
	 */
	protected String Key;
	
	protected Type Value;
	/**
	 * @uml.property  name="description"
	 */
	protected String Description;
	
	public Property() {
		// TODO Auto-generated constructor stub
	}
	
	abstract Property find();
}