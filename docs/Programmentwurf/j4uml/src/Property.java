
abstract public class Property {

	/**
	 * @uml.property  name="key"
	 */
	protected String Key;
	/**
	 * @uml.property  name="description"
	 */
	protected String Description;
	
	public Property() {
		// TODO Auto-generated constructor stub
	}
	
	abstract Property find();
	
}
