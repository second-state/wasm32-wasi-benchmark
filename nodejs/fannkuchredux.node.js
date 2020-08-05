class fannkuchredux
{
   fannkuch(n) {
      var perm = new Array(n);
      var perm1 = new Array(n);
      var count = new Array(n);
      var maxFlipsCount = 0;
      var permCount = 0;
      var checksum = 0;

      for(i=0; i<n; i++) perm1[i] = i;
      var r = n;

      while (true) {

         while (r != 1) { count[r-1] = r; r --; }

         for(i=0; i<n; i++) perm[i] = perm1[i];
         var flipsCount = 0;
         var k=perm[0];
         var temp = 0;

         while ( !((k=perm[0]) == 0) ) {
            var k2 = (k+1) >> 1;
            for(i=0; i<k2; i++) {
               temp = perm[i]; 
               perm[i] = perm[k-i]; 
               perm[k-i] = temp;
            }
            flipsCount += 1;
         }

         maxFlipsCount = Math.max(maxFlipsCount, flipsCount);
         checksum += (permCount%2 == 0 ? flipsCount : -flipsCount);

         // Use incremental change to generate another permutation
         while (true) {
            if (r == n) {
	            console.log(checksum);
	            return maxFlipsCount;
	        }
            var perm0 = perm1[0];
            var i = 0;
            var j = 0;
            while (i < r) {
               j = i + 1;
               perm1[i] = perm1[j];
               i = j;
            }
            perm1[r] = perm0;

            count[r] = count[r] - 1;
            if (count[r] > 0) break;
            r++;
         }

         permCount++;
      }
   }
   /*
   main(args) {
      var n = 7;
      if (args.length > 0) n = Integer.parseInt(args[0]);
      console.log("Pfannkuchen("+n+") = "+fannkuch(n));
   }*/
}

var n = +process.argv[2];

console.log("PROGRAM OUTPUT:");
let v = new fannkuchredux();
console.log("Pfannkuchen("+n+") = "+ v.fannkuch(n));

