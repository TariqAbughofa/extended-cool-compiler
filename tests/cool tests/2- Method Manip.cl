namespace Methods
{
	public class Fibb is
		public RecFibb(x:Int):Int is
			if (x=1) then
				return 1;
			else
				if (x=2) then
					return 1;
				else
					return (RecFibb(x-1) + RecFibb(x-2));
				fi;
			fi;
		end
		public IterFibb(x:Int):Int is
			if (x=1) then
				return 1;
			else
				if (x=2) then
					return 1;
				else
					begin
						let(i:Int<-3, a:Int<-1, b:Int<-1, c) in
							c<-a+b;
							if (i=x) then
								return c;
							else
								begin
									a<-b;
									b<-c;
								end;
							fi;
							i <- i+1;
						end;
					end
				fi;
			fi;
		end
	end
	public class Main is
		public main():SELF_TYPE is
			let (f:Fibb <- new Fibb()) in
				if (not(f.IterFibb(10) = RecFibb(10))) then
					abort();
				else
					IO.out_string("OK, go on");
				fi;
			end
			return self;
		end
	end
}