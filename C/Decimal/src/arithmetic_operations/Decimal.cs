using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace SoloLearn
{
	class Program
	{
		static void Main(string[] args)
		{

			decimal dec_1 = Decimal.MaxValue;
			// dec_1 = 10000000000000000000000000000M;
			Console.WriteLine(dec_1);
			dec_1 = -12365767456475664586545.645645M;
			dec_1 = 7.111M;
			//dec_1 = dec_1 * 7.111M;
			Console.WriteLine(dec_1);
			Console.WriteLine("\n");

        	int[] arr = Decimal.GetBits(dec_1); 
  
        	for (int i = 3; i >= 0; i--) {
				string binary = Convert.ToString(arr[i], 2).PadLeft(32, '0');
				Console.WriteLine(binary);
			}
           	 

		}
	}
}

