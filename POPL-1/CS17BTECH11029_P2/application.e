note
	description: "stable marriage problem"

class
	APPLICATION
		-- Stable Marriage Application Class

create
	make
feature
	n:INTEGER
		-- Number of men / women
	men:ARRAY2[INTEGER]
		-- Men prefrences
	women:ARRAY2[INTEGER]
		-- Women prefrences
	combination:ARRAY[INTEGER]
		-- final combination
	free_women:ARRAY[BOOLEAN]
		-- status of women (free/engaged)
feature
	make
		local
			i:INTEGER
			j:INTEGER
			x:LIST[STRING]
		do
			io.read_integer
			n:=io.last_integer
			create men.make_filled(0,n,n)
			create women.make_filled (0,n,n)
			create combination.make_filled (0, 1,n)
			create free_women.make_filled (True, 1,n)
				-- intialising Arrays by default values
			from
				i:=1
			invariant
				bounds : i>0 and i<=2*n+1
			until
				i>2*n
			loop
				io.read_line
				x:= io.last_string.split (' ')
					-- read a line ans split by spaces
				from
					j:=1
				invariant
					bounds : j>0 and j<=n+1
				until
					j>n
				loop
					if i<=n then
						women[x[1].to_integer,j]:= x[1+j].to_integer
							-- fill in women prefrences
					else
						men[x[1].to_integer,j]:= x[1+j].to_integer
							-- fill in men prefrences
					end
					j:=j+1
				end
				i:=i+1
			end
			get_matching
				-- run the algorithm to find matching pair
			print_matching
			rescue
				print("INVALID")
				io.new_line
		end

	get_free_women:INTEGER
		-- return a free women otherwise return N+1
		require
			trivial: n>0 and men.height=n and men.width=n and women.height=n and women.width=n and combination.upper=n and free_women.upper=n
				-- validty of class members . Trivially they should hold always
		local
			i:INTEGER
		do
			Result:=n+1
			from
				i:=1
			invariant
				bounds: i>0 and i<=n+1
				valid_woman : Result>0 and Result<=N+1
					-- woman should be valid . woman=N+1 means no woman
			until
				i>n
			loop
				if free_women[i]=True then
					Result:=i
					i:=n+1
				else
					i:=i+1
				end
			end
			ensure
				trivial : n>0 and men.height=n and men.width=n and women.height=n and women.width=n and combination.upper=n and free_women.upper=n
					-- trivially should hold
				not_changed_arrays : (men=old men) and (women=old women) and (combination=old combination) and (free_women=old free_women)
					--no arrays should be modified
				valid_woman : Result>0 and Result<=N+1
					-- result must be valid one
			rescue
				print("INVALID")
				io.new_line
		end

	get_women_priority(m,w:INTEGER):INTEGER
		-- return the priority of women in a man's list
		-- priority is from 1 to N
		-- if women is invalid then return N+1
		require
			trivial : n>0 and men.height=n and men.width=n and women.height=n and women.width=n and combination.upper=n and free_women.upper=n
				-- trivially should hold
			valid_man : m>0 and m<=n
			valid_woman : w>0
				-- man and woman should be valid.
		local
			i:INTEGER
		do
			Result:=n+1
			from
				i:=1
			invariant
				bounds : i>0 and i<=n+1
				result_condition : Result>0 and Result<=N+1
					-- result should always be bounded
				valid_man_woman : m>0 and m<=n and w>0
			until
				i>n
			loop
				if men[m,i]=w then
					Result:=i
					i:=n+1
				else
					i:=i+1
				end
			end
			ensure
				trivial : n>0 and men.height=n and men.width=n and women.height=n and women.width=n and combination.upper=n and free_women.upper=n
					-- trivially should hold
				not_changed_arrays : (men=old men) and (women=old women) and (combination=old combination) and (free_women=old free_women)
					-- arrays should not changed
				valid_woman : Result>0 and Result<=N+1
					-- result should be valid
			rescue
				print("INVALID")
				io.new_line
		end

	get_matching
		-- Algorithm to find a mapping (m,w)
		require
			trivial: n>0 and men.height=n and men.width=n and women.height=n and women.width=n and combination.upper=n and free_women.upper=n
				-- trivially should hold
		local
			free:INTEGER
			w,m,w1:INTEGER
			j:INTEGER
		do
			w:=n+1
			m:=n+1
			w1:=n+1
			from
				free:=n
			invariant
				bounds : free<=n and free>=0
				valid_woman : w>0 and w<=n+1 and w1>0 and w1<=n+1
				valid_man : m>0 and m<=n+1
					-- man and woman should be bounded always
			until
				free<1
			loop
				w:= get_free_women
					-- find a free woman
				from
					j:=1
				invariant
					bounds : j>0 and j<=n+1
					valid_woman : w>0 and w<=n+1 and w1>0 and w1<=n+1
					valid_man : m>0 and m<=n+1
						-- man and woman should be bounded always
				until
					j>n or free_women[w]=False
				loop
					m:=women[w,j]
						-- take a man
					if combination[m]=0 then
							-- check if man is free . if its free make pair
						combination[m]:=w
						free_women[w]:=false
						free:=free-1
					else
						-- man is not free than check if priority of w is greater than w1 or not
						w1:=combination[m]
						if get_women_priority(m,w)<get_women_priority(m,w1) then
							combination[m]:=w
							free_women[w]:=false
							free_women[w1]:=true
						end
					end
					j:=j+1
				end
			end
			ensure
				trivial: n>0 and men.height=n and men.width=n and women.height=n and women.width=n and combination.upper=n and free_women.upper=n
					-- trivially should hold
				no_free_women : get_free_women=n+1
					-- No free women should be there
				unique_mapping : unique_matching=true
					-- mapping must be unique
				not_changed_arrays :  (men=old men) and (women=old women)
					-- combination and free_women may change but these two arrays must not change
			rescue
				print("INVALID")
				io.new_line
		end
	print_matching
		-- print the mapping
		require
			trivial: n>0 and men.height=n and men.width=n and women.height=n and women.width=n and combination.upper=n and free_women.upper=n
				-- trivially should hold
		local
			free:INTEGER
		do
			from
				free:=1
			invariant
				bounds: free>0 and free<=n+1
					-- bounds
			until
				free>n
			loop
				print(combination[free])
					-- print the mapping
				io.new_line
				free:=free+1
			end
			ensure
				trivial: n>0 and men.height=n and men.width=n and women.height=n and women.width=n and combination.upper=n and free_women.upper=n
				not_changed_arrays : (men=old men) and (women=old women) and (combination=old combination) and (free_women=old free_women)
					-- trivial conditions
			rescue
				print("INVALID")
				io.new_line
		end

	unique_matching:BOOLEAN
		-- check if mapping is unique
		-- checking if count of every woman in mapping is exactly one
		require
			trivial: n>0 and men.height=n and men.width=n and women.height=n and women.width=n and combination.upper=n and free_women.upper=n
				-- trivially should hold
		local
			i:INTEGER
			count:ARRAY[INTEGER]
		do
			Result:=true
			create count.make_filled(0,1,n)
			from
				i:=1
			invariant
				bounds : i>0 and i<=n+1
				 -- bounds
			until
				i>n
			loop
				-- finding count
				count[combination[i]]:=count[combination[i]]+1
				i:=i+1
			end
			from
				i:=1
			invariant
				bounds : i>0 and i<=n+1
			until
				i>n
			loop
				-- check if count of every women is exactly one
				if count[i]/=1 then
					Result:=false
					i:=i+n
				else
					i:=i+1
				end
			end
			ensure
				trivial : n>0 and men.height=n and men.width=n and women.height=n and women.width=n and combination.upper=n and free_women.upper=n
				not_changed_arrays : (men=old men) and (women=old women) and (combination=old combination) and (free_women=old free_women)
					-- trivially should hold
			rescue
				print("INVALID")
				io.new_line
		end

invariant
	trivial : n>0 and men.height=n and men.width=n and women.height=n and women.width=n and combination.upper=n and free_women.upper=n
		-- trivial class invarinat

end
