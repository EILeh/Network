Network

Program stores information of who has recruited who. Program asks the user to
give a command S, P, C, D or Q. Commands can be given also as a lowercase
letters.

S (=store): Takes two persons' identifiers as a string parameters. First
parameter is a person who has recruited the person as a second parameter.

P (=print): Takes the person's identifier as string parameter and prints all
the others that the particular person has recruited and who they have
recruited. They are printed in the order where they are recruited and if
person 1 has recruited person 2 and 3 and person 3 has recruited person 4,
would it look like this:
P 1
..2
..3
....4
C (=count): Takes the person's identifier as a parameter and prints the size
of the current person's subnet.

D (=depth=: Takes the person's identifier as a parameter and prints the depth
of the current person's subnet meaning the longest recruited line that the
person has starting from the person themself. If person 1 has recruited
person 2 and person 2 has recruited person 3, the depth on the person 1's
subnet would be 3.

Q (=quit): Program closes.
