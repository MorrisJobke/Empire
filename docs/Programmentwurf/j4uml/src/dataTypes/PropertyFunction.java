package dataTypes;

public class PropertyFunction extends Property{

	/**
	 * @uml.property  name="mapFunction"
	 * @uml.associationEnd  readOnly="true"
	 */
	private FunctionPointer MapFunction;
	/**
	 * @uml.property  name="reduceFunction"
	 * @uml.associationEnd  readOnly="true"
	 */
	private FunctionPointer ReduceFunction;
	
	@Override
	Property find() {
		// TODO Auto-generated method stub
		return null;
	}
	
	public void RegisterMapFunction(FunctionPointer pFunc){
		
	}

	public void RegisterReduceFunction(FunctionPointer pFunc){
		
	}

	boolean create(String id) {
		// TODO Auto-generated method stub
		return false;
	}
}
