Chila Tools
===========

This is a collection of C++ tools. Right now there's only one tool called 
Connection Tools.

Connection Tools
----------------

    Connection Tools allows you to create an application in a module-oriented 
way. The way to do this is by defining Modules using an easy XML format,
and a Application that makes the Modules comunicate between each other. The 
Application is also defined in XML. Once you've defined those, two tools will 
generate C++ code that you can use to build the actual application.

    The generated code is non-intrusive, that is, you "use" the code, but you
do not write over it. So this means no reverse engineering of any kind.
 

Inside a Module, you define:

- Arguments: These are the basic comunication elements betwen Modules, they 
are the CONCEPTS that Modules comunicate betwen each other. Module Arguments
map directly the target language's argument. Arguments are unique inside a 
Module, so for example you cannot have two 'id' arguments, each one meaning 
something different depending on their contexts, because the Module is the 
actual context, not the function that uses the argument.

- Functions: Functions are the VERBS that are used to comunicate the 
arguments. There are two kinds of Module Functions:

    - Actions: These are the actions that a Module can perform. For example,
if your Module can send a message over the network, it could have something
like 'sendMessage(client, message)', there 'sendMessage' is the action, and
'client' and 'message' the arguments.

    - Events: These are the events that a Module "fires". For example, if
a message has arrived, the Module could an event like 
'messageReceived(client, message)', where 'messageReceived' is the event,
and 'client' and 'message' the arguments.

    Once you've done defining Modules, you need to make'em talk. You do this 
defining an Application. What you basically do inside an Application is to 
join Events with Actions. You do this by joining one Module's Event to one 
or many Actions from one or many other Modules. So for example if you have a 
module called 'messageManager', that has an event called 'messageArrived', a 
Module called 'messageProcessor' with an Action called 'processMessage', and 
a Module called 'logger' that has an Action called 'logArrivedMessage', you 
basically say that 'messageManager.messageArrived' will be linked to 
'messageManager.processMessage' and 'logger.logArrivedMessage'. So when
you run your application, once the event 'messageManager.messageArrived'
is fired, it will execute 'messageManager.processMessage' and 
'logger.logArrivedMessage' Actions. 
That's the easy part :D, the hard part is to make one Module Event' 
Arguments correspond to the executed Module Action' ones. The good thing 
is... defining that it's actually easy. The hard part is done by the 
generated code, so you don't have to care about that.

    So let's do this step by step: first, you need to create a "common 
language" for the Modules to comunicate. To do this, you create something
called Argument Aliases. An Argument Alias is an alias for a Module Argument.
This Alias is unique inside the Application, as an Argument is unique inside
a Module. Actually, an Argument Alias can be an alias for many Arguments, 
but only for one within a Module. If two Arguments share the same Alias,
they are said to be "meaining-equivalent". So for example, if you have a 
Module with an argument called 'client', and another Module with an Argument 
also called 'client', and both arguments "mean" the same thing inside the 
Application, then they can have an alias also called 'client'. The same
thing can go for a 'message' Argument. So, if 'messageManager.messageArrived'
has a 'client' and 'message' Arguments, and 'logger.logMessage' has also
a 'client' and 'message' Arguments, you can correspond them with their
respective aliases. What happens if the called Action does not use a 
provided Alias? It's simply discarded. What if it uses an Alias not provided
by the Event? That's an error in the definition and must be corrected.

(Terrible "3rd. time" Friday soccer hangover headache while writing this, ok 
nevermind).

    So far so good, but what about the situations where there's no match?
For instance, what if 'logger' does not take a 'message', but the message's
id?  We can certainly extract the id from the message, but how do we 
express that? Well to do that, we need some thing called "Argument Provider".
These Argument Providers are objects that can take some Aliases, and provide
some Aliases. So they can be represented as 'provider(aliases) --> aliases'.
These providers will be created at the time the calls to the Actions are 
made, and will be created by some objects called "Argument Provider 
Creators". These can be expresed the same way as the providers. So what
we do is to declare this APCs inside the Application's definition, and then
used in each Module's connections (if needed).

    APCs can be "stacked", so you can have many creators stacked for some
connections. So the way to express a connection (links between an Event an 
Actions) is something like: event(<apc1...apcN>, <action1...actionN>).

    The effect of an APC for a given connection is to "augment" the 
provided Aliases. So if a given Event provides the arguments 'client' and 
'message', and we stack an APC that provides the message's 'id', the 
connection ends up providing these three Aliases altogeter, for every
Action called. A given AP takes a given Alias from it's preceeding APC
in the stack, if not found, looks in the preceeding's preceeding, an so
until the first AP. If the alias is still not found, it looked for 
in the Event itself. If it's still not found, it's considered a design 
error and must be corrected. The Action itself follows this same Alias
looking algorithm, all the way to the calling Event. This means you can
actually change the value transported by a given Alias inside an AP, 
by takind this Alias and providing the same Alias. The algorithm guarantees
that the later will be used.
    In the C++ implementation, this "algorithm" is actually a compile-time
one, so there's no performance overhead for it. 

    So once you have the Modules and the Application defined, you proceed to
generate C++ code from them. For the Modules, you use the 
'connectorGenerator' tool, and for the Application, you use the 
'applicationGenerator' tool. 

- connectorGenerator: This tool generates something called a "Connector". 
A Connector is a template class that contains code for the Module's
Arguments and Functions. You need to include this Connector inside your
Module and connect your methods to the Actions provided by the Connector.
The connector also provides the Events to be fired by the Module. The
template parameter provided to the Connector is one that contains the 
Argument's C++ types to be used. 

- applicationGenerator: This tool generates the Application code. This code
connects the Connectors between themselves. Note that your Modules are
not actually the ones connected, it's their Connectors the ones that
are. This allows the Connector code to be separated from the Module
implementation itself, and not to be coupled to it in any way. This 
makes dependencies minimal, and compilation times controlled.

    You can also generate documentation form the Module and Application
definitions, with the 'docGenerator' tool. This tool generates documentation
in DocBook format. It's still experimental and not quite finished but 
it's usable. The posibility to also generate documentation out of your
application design is a *very good thing*, in case you did not notice.
This means that your design will always be synchronized with your code
AND your documentation!. All at once. And it get's even better: the 
generation tools can be called at compilation time!. So you can change your 
design and hit "compile" and everything will be updated to match the change.   

    Yes, this can be said to be a UML alternative, at least for some parts 
of it, but way less brain damaging.

    The code generation tools actually generate code that use heavily
templated code, and it's this code that does all the actual magic, at
compile time. This means that the generated code is 1-1 with the actual
design. You can actually build your application without the generation
tools, but it's obviously discouraged since you will not have the 
design written in a easily parseable way to, say, generate documentation
or be managed by a graphical tool (to be done). 
    
    A test application for the generated code can be found in 
'connectionTools/bindTest', and an example application that uses the
generation tools can be found ant 'connectionTools/appTest'. You can
learn how to use tools by looking at them, they're very simple and
to the point. 

    For more complex applications, I'm pretty sure you can create 
hierarchies of Applications that can be presented as Modules themselves,
in order to express subsystems of the application.

    Because of the way Modules are defined, they can be easily reused by
other applications. 

    Now some implementation recomendations:
    - Keep your Actions nonblocking and fast. The caller Module should not
wait much for the callee to finish. It should be as fast as posible. If the
Action takes some time, put it inside a task queue for later processing. 
This pattern is also recomended for two reasons:
        1- You can have a global task queue that can multiplex multiple
           actions, thus keeping the application monothreaded. Monothreaded
           applications are *good*, because they do not have race-conditions
           and they maximize predictibility.
        2- You detach the Action's stack from the Event's stack, so if the
           Action calls an Event, and this event is connected some Action that
           belongs to the caller Module, the "single-threaded-race-condition'
           is avoided.

    The way I create my applications is to have a main task queue 
(boost::asio::io_service) where "normally" Actions are posted. The main
thread consumes the Actions and executes them. When an Action implies a 
blocking call, I mask the Action behind a non-blocking interface, which 
normally implies posting the action to a queue that's being hooked some
different(s) thread(s). When the execution of the Action finishes, the
result is normally in the form of an Event call, and posted back to the
main thread. So, when you need to "simulate" asynchronicity, you can use 
threads, but the main application's logic remains in the main thread.
The good thing of all this is that where whe actions are executed is 
an actual implementation detail, not a design one.

    There are some exceptions to the post-event-back-to-main-thread rule.
One of them is the release of a needed resource by the called Action, for 
instance a database connection. If you post the event that calls this Action,
it's execution can take some time to take place. If there are no more 
connections available while this, no processing can take place in this lapse. 
This prevents the processing of data to fully saturate the worker threads, 
and thus preventing optimal parallelism of processing. One solution could be 
to have more database connections than worker threads, but a db-connection is 
normally a resource that is meant not to be overused. So in this situation, 
the event should actually run immediately in the Action's worker thread, 
which would normally trigger the immediate execution of another processing 
Action right there in that stack (using a database connection pool that 
posts request and executes them when a connection is available). Since that 
processing action will normally be posted in the worker threads' task queue, 
the stack is detached from the caller worker thread right there. But, we 
must also note that the called event could trigger other types of Actions, 
like logging, counting, etc. These Actions should be posted to the main queue 
and not ran immediately, to avoid any kind of race-condition. One more reason 
to posts normal Actions to a main thread. Note that the processing Actions 
are also posted, but in the worker threads' queue.

    So we can pretty much conclude that most Actions should be posted to some
task queue. If we assume this to be the law, we can also assume that Events
should be ran immediately in the caller's thread. There are thou, some 
Actions that are too small to justify posting them, but in the other hand
if these actions could be called from an Event that's called from a queue 
other than the main one, a race condition could arise. Probably all Actions
should be posted to some task queue, and if this is the case, I will have
to add some facility to do this transparently (but optional), without the
need that the implementer posts them manually. 

    So that's it. I hope you'll like it. 
    
    (Good news, my headache is gone!)


