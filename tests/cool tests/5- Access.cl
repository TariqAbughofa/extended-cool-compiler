namespace Privs
{
	internal class User is
		private password: String;
		protected isLocked: Bool;
		public username: String;
		public init(username:String, password:String):SELF_TYPE is
			self.username<-username;
			self.password<-password;
			self.isLocked<-true;
			return self;
		end
		public Lock():Bool is
			let(tmp:Bool <- self.isLocked) in 
				self.isLocked <- true;
				return tmp;
			end
			return false;
		end
		public unLock():Bool is
			let(tmp:Bool <- self.isLocked) in 
				self.isLocked <- false;
				return tmp;
			end
			return true;
		end
	end
	internal class Admin inherits User is
		public init(username:String, password:String):SELF_TYPE is
			self.username<-username; (* public access, OK *)
			self.password<-password; (* private access, error *)
			self.isLocked<-true;	 (* protected access, OK *)
			return self;	
		end
	end
	internal class Main is
		u:User <- new User()
		a:Admin <- new Admin()
		public main():SELF_TYPE is
			u.init("Ubai", "pa$$word");
			a.init("Ubai", "pa$$word"); (* Generates an error *)
			u.isLocked<-false;	 (* protected access, error *)
			if (u.unLock()) then
				out_string("u is ready");
			else
				out_string("u is not ready");
			fi
		end
	end
}