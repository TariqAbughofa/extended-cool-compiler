namespace OverLoading
{
	internal class A is
		public f(x:Int):Int is
			IO.out_string("int f");
			return x;
		end
		public f(x:String):String is
			IO.out_string("string f");
			return x;
		end
		
	end
	internal class Main is
		a:A <- new A();
		public main():SELF_TYPE is
			IO.out_int(a.f(5));
			IO.out_string(a.f("Hello"));
			return self;
		end
	end
}
