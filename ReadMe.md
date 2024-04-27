Project setup for the geometric algebra should be relatively straightforward:
there are no external libraries, the project is just a listing of h and cpp
files for basic IO, keyword and basic operation errata and custom math.
In the worst case, the project given may not cooperate in finding the files.
I use version control on the source files external to where I store binaries
and project files, so those may not be compilable on another machine.
If this is the case, making a new empty project and dragging files into it
is all that should be required however (given the simplicity of files used).

Main.cpp is a driver file running the basic unit tests for GA objects.  I am
remiss to say, I wasn't able to get the dual quaternion rotor (GP301) quite
functional however, and this was ultimately the stopping point for progress.
The even subalgebra object is quite core to the function of rotors, and it
seems like it is almost working, but something is amiss.  I have been over
it time and again, but I'm not sure what might be wrong.  Still, if the
inverse isn't coming out to the identity, this precludes sandwiches working
which precludes modeling reflection composition.  I feel confident my work
is close enough to correct that what I have learned is accurate, and the
fundamentals are something I have internalized well enough, but I can't
deny I had hoped to have gotten farthur as well.  I'm not sure why those
who I have reached out to for help in the field have been less than helpful
in directly addressing what I believe to be the problem, but I will certainly
keep working at this as a personal project.  The math seems coherent and
worthwhile enough that I do feel it is an inevitability that I will work
through these issues in the future.  I hope my study guide suffices in
bolstering the sum worth of this project, and if you have any success looking
into the issue, I would be eager to hear your response.
Thanks for your time and help.

- Ari Surprise
