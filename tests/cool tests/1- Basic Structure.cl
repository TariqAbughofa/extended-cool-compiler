namespace outer{
public class Main is
	internal x:Int;
	private y:String<-"Hello";
	private z:Int[5];
	protected ToString():String is
		return y;
	end
	private Check(x:Int):Bool is
		if (self.x<x) then
			return true;
		else 
			return self.x<z[0];
		fi;
	end
	public init(x:Int):Void is
		i:Int<-0;
		while (i<5) loop
			z[i] <- x;
			i<-i+1;
		pool;
		self.x<-x;
	end
	public init(x:Int, y:String):Void is
		init(x);
		self.y <- y;
	end
	
	public readInput():SELF_TYPE is
		self.y <- IO.in_string();
		self.x <- IO.in_int();
		init(self.x);
		IO.out_string("OK! Done");
		return self;
	end

	public main():SELF_TYPE is
		readInput();
		IO.out_string(self.ToString());
		return self;
	end
	
end
}