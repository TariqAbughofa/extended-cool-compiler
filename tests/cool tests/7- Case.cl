namespace BigTree
{
	public class P is  virtual SayName():string is return "P" end  end
	public class C1 inherits P is  override SayName():string is return "C1" end  end
	public class C2 inherits P is  override SayName():string is return "C2" end  end
	public class C3 inherits P is  override SayName():string is return "C3" end  end
	public class G1C1 inherits C1 is  override SayName():string is return "G1C1" end  end
	public class G1C2 inherits C1 is  override SayName():string is return "G1C2" end  end
	public class G1C3 inherits C1 is  override SayName():string is return "G1C3" end  end
	public class G2C1 inherits C2 is  override SayName():string is return "G2C1" end  end
	public class G2C2 inherits C2 is  override SayName():string is return "G2C2" end  end
	public class G2C3 inherits C2 is  override SayName():string is return "G2C3" end  end
	public class Main is
		Obj:P <- new G2C2();
		public main():SELF_TYPE is
			case Obj of 
			{
				x: G1C1 => out_string(x.SayName());
				x: G1C2 => out_string(x.SayName());
				x: G1C3 => out_string(x.SayName());
				x: G2C1 => out_string(x.SayName());
				x: G2C2 => out_string(x.SayName());
				x: G2C3 => out_string(x.SayName());
			}
			esac (* must print G2C2, the 5th option *)
			case Obj of 
			{
				x: C1  => out_string (x.SayName());
				x: C2  => out_string (x.SayName());
				x: C3  => out_string (x.SayName());
			}
			esac (* also print G2C2, picking the 2nd option *)
			return self;
		end
	end
}