namespace Override
{
	public class Fruit is
		static counter:Int <- 0;
		virtual SayName():String is
			Fruit.counter <- Fruit.counter+1;
			return "Fruit";
		end
		public printCounter():SELF_TYPE is
			out_int(Fruit.counter);
			return self;
		end
		public test():Int is
			return 5;
		end
	end
	public class Apple inherits Fruit is
		override SayName():String is
			Fruit.counter <- Fruit.counter+1;
			return "Apple";
		end
		public test():String is
			return "Hello";
		end
	end
	public class Main is
		public main():SELF_TYPE is
			let (tmpObj:Fruit <- new Fruit()) in
				out_string(tmpObj.SayName());
				tmpObj.printCounter();
			end
			let (tmpObj:Fruit <- new Apple()) in
				out_string(tmpObj.SayName());		(* prints out Apple *)
				out_int(tmpObj.printCounter().test()); 
				(* error, printCounter returns type Apple, At which test must return a string not an int. Therefore, Must have out_string instead *)
				out_int((tmpObj.printCounter()@Override.Fruit).test());  (* OK *)
			end
			return self;
		end
	end
}