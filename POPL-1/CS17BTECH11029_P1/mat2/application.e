note
	description: "Matrix application root class"
	date: "$Date$"
	revision: "$Revision$"

class
	APPLICATION

inherit
	ARGUMENTS_32

create
	make
feature
    Matrix:ARRAY2[REAL]
    inverse:ARRAY2[REAL]
    n:INTEGER
    exists:BOOLEAN
           	-- local 'MATRIX' object and determinant
feature

	make
		local
			i,j:INTEGER
			x:LIST[STRING]
		do
			io.read_integer
			n:=io.last_integer
         	create Matrix.make_filled(0.0,n,n)
         	create inverse.make_filled(0.0,n,2*n)
         	from
         		i:=1
         	invariant
         		row_range : i>0 and i<=n+1
         			-- loop invariants
         	until
         		i>n
         	loop
         		io.read_line
         		x:= io.last_string.split (' ')
         		from
         			j:= 1
         		invariant
         			column_range : j>0 and j<=n+1
         			-- loop invariants
         		until
         			j >n
         		loop
         			Matrix[i,j] := x[j].to_real
         			inverse[i,j]:= x[j].to_real
         			j:=j+1
         		end
         		i:=i+1
         	end
         	exists:=true
         	invert
         	if exists then
         		print_inv
         	end
         	rescue
         		print("INVALID")
				io.new_line
		end

	invert
		local
			i,j,k,m:INTEGER
			zero_sum,first_non_zero:INTEGER
			x:ARRAY[REAL]
		do
			create x.make_filled(0.0,1,2*n)
			create_identity
			i:=1
			from
				j:=1
			until
				j>n
			loop
				first_non_zero := 0
				zero_sum:=0
				from
					k:=i
				until
					k>n
				loop
					if inverse[k,j]/=0 then
						zero_sum:=zero_sum+1
					end

					if first_non_zero=0 and inverse[k,j]/=0 then
						first_non_zero:=k
					end
					k:=k+1
				end
				if zero_sum=0 then
						exists:=false
						print("INVALID")
						io.new_line
						j:=1+n
				else
					if first_non_zero/=i then
						swap_row(i,first_non_zero)
					end
					from
						m:=1
					until
						m>2*n
					loop
						x[m]:=inverse[i,m]/inverse[i,j]
						m:=m+1
					end
					from
						m:=1
					until
						m>2*n
					loop
						inverse[i,m]:= x[m]
						m:=m+1
					end
					from
						k:=1
					until
						k>n
					loop
						if k/=i then
							from
								m:=1
							until
								m>2*n
							loop
								x[m]:=inverse[k,j]*inverse[i,m]
								m:=m+1
							end
							from
								m:=1
							until
								m>2*n
							loop
								inverse[k,m]:=inverse[k,m]-x[m]
								m:=m+1
							end
						end
						k:=k+1
					end
					if i=n+1 or j=n+1 then
						j:=1+n
					else
						j:=j+1
						i:=i+1
					end
				end
			end
		end

	swap_row(i,p:INTEGER)
		local
			k:INTEGER
			a:ARRAY[REAL]
		do
			create a.make_filled(0,1,2*n)
			from
				k:=1
			until
				k>2*n
			loop
				a[k]:=inverse[i,k]
				inverse[i,k]:=inverse[p,k]
				inverse[p,k]:=a[k]
				k:=k+1
			end
		end

	create_identity
		local
			i:INTEGER
		do
			from
				i:=1
			until
				i>n
			loop
				inverse[i,i+n]:=1
				i:=i+1
			end
		end

	print_inv
		local
			i:INTEGER
			j:INTEGER
		do
			from
				i:=1
			until
				i>n
			loop
				from
					j:=n+1
				until
					j>2*n
				loop
					if inverse[i,j]=-0.0 then
						print("0")
					else
						print(inverse[i,j])
					end
					print(" ")
					j:=j+1
				end
				io.new_line
				i:=i+1
			end
		end

end
