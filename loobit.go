/* Il est apparement encore compliqué d'interfacé go et C
   code entierement en go
*/

package main

import "fmt"

type ArrayOfDouble [] double;
type ArrayOfBool [] bool;

func (p *ArrayOfDouble) accumulBitmasque(bitmasque *ArrayOfBool) double {
	var somme double
	for i=0; i <= p.length(); i++ {
		if bitmasque[i] {
			somme = somme + p[i];
		}
	

	return somme
}

func main() {
	fmt.Println("Coucou Grégory !");
	var tableau [] double

}