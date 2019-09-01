namespace Shapes
{
	public class Shape is
		public x:Int <- 5;
		public y:Int <- 10;
	
		public shapeMethod():Void is
			IO.out_string("shape method");
		end
	end
	
	public class Circle inherits  Shape is
		public radius:Float <- 2.5;
		
		public circleMethod():Void is
			IO.out_string("circle method");
		end
	end
	public class Main is
		public main():SELF_TYPE is
			let (circle:Circle  <- new Circle()) in
				circle.circleMethod();
				circle.shapeMethod();
			end
			return self;
		end
	end
}

