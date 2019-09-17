		#

.name"Batman"			



;;
.comment 		"This
	city
	needs
	me" ;;;;



	;;





		loop:



	        sti r1,  %1      , 			%:live
live:	        live %0
	        ld %0,       r2
test:	        zjmp %:loop
