note
	description: "Inverse of a Matrix"
	author : "Puneet Mangla"

class
	APPLICATION

inherit
	ARGUMENTS_32

create
	make
feature
    Matrix:ARRAY2[REAL]
    	-- actual matrix
    inverse:ARRAY2[REAL]
    	-- Augmented matrix A|I
    n:INTEGER
    	-- dimension
    exists:BOOLEAN
        -- inverse exists or not
    eps :REAL
    	-- epsilon for inverse checking
feature

	make
		local
			i,j:INTEGER
			x:LIST[STRING]
		do
			eps:= 0.001
			io.read_integer
			n:=io.last_integer
				-- read input dimension
         	create Matrix.make_filled(0.0,n,n)
         	create inverse.make_filled(0.0,n,2*n)
         		-- initialise matrix
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
         				-- fill in values in matrix
         			j:=j+1
         		end
         		i:=i+1
         	end
         	exists:=true
         		-- let inverse exists
         	invert
         		-- invert matrix
         	if exists then
         		print_inv
         			-- if exists then print inverse
         	end
         	rescue
         		print("INVALID")
				io.new_line
		end

	invert
		require
			trivial : n>0 and Matrix.height =n and Matrix.width=n and inverse.height=n and inverse.width=2*n and exists
				-- trivial conditions
		local
			i,j,k,m:INTEGER
			zero_sum,first_non_zero:INTEGER
			x:ARRAY[REAL]
		do
			-- GAUSS JORDAN ALGORITHM
			create x.make_filled(0.0,1,2*n)
				-- dummy arrays
			create_identity
				-- create the Augmented Matrix A|I
			i:=1
			from
				j:=1
			invariant
				bounds : j>0 and j<=n+1 and i>0 and i<=n+1
					-- loop invariants
			until
				j>n
			loop
				first_non_zero := 0
				zero_sum:=0
				from
					k:=i
				invariant
					bounds : k>0 and k<=n+1 and j>0 and j<=n+1 and i>0 and i<=n+1
					local_bounds : zero_sum>=0 and zero_sum<=n and first_non_zero>=0 and first_non_zero<=n
				until
					k>n
				loop
					if inverse[k,j]/=0 then
						zero_sum:=zero_sum+1
							-- find number of non zero elements
					end

					if first_non_zero=0 and inverse[k,j]/=0 then
						first_non_zero:=k
							-- pick first non zero element
					end
					k:=k+1
				end

				if zero_sum=0 then
						-- if all are zeros then for sure inverse doesnt exists
						-- terminate loop and set exists = false
						exists:=false
						print("INVALID")
						io.new_line
						j:=1+n
				else
					if first_non_zero/=i then
						-- if current row is not pivot then swap the rows
						swap_row(i,first_non_zero)
					end
					-- divide all elements in that row by pivot to make pivot 1.0
					from
						m:=1
					invariant
						bounds: m>0 and m<=2*n+1
							--loop invarinats
					until
						m>2*n
					loop
						x[m]:=inverse[i,m]/inverse[i,j]
							-- dividing by pivot
						m:=m+1
					end
					from
						m:=1
					invariant
						bounds: m>0 and m<=2*n+1
							--loop invarinats
					until
						m>2*n
					loop
						inverse[i,m]:= x[m]
							-- set the new row where pivot is one
						m:=m+1
					end

					-- Elementary transformation on all rows below i , make the corresponding column 0
					from
						k:=1
					invariant
						bounds: k>0 and k<=n+1
							--loop invariants
					until
						k>n
					loop
						-- LOOP for elementary tranformation i.e gauss elimination
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
							-- terminating condition
					else
						j:=j+1
						i:=i+1
					end
				end
			end
			ensure
				trivial : n>0 and Matrix.height =n and Matrix.width=n and inverse.height=n and inverse.width=2*n
					-- trivial conditions
				matrix_not_changed : Matrix = old Matrix
				true_inverse : check_inverse
					-- check if AA_inverse = A_inverseA = I
			rescue
         		print("INVALID")
				io.new_line
		end

	swap_row(i,p:INTEGER)
		require
			trivial : n>0 and Matrix.height =n and Matrix.width=n and inverse.height=n and inverse.width=2*n and exists
				-- trivial conditions
			bounds : i>0 and i<=n and p>0 and p<=n and i/=p
				-- swapping rows should be different
		local
			k:INTEGER
			a:ARRAY[REAL]
		do
			-- SWAPPING using THIRD VARIABLE
			create a.make_filled(0,1,2*n)
			from
				k:=1
			invariant
				bounds:k>0 and k<=2*n+1
			until
				k>2*n
			loop
				a[k]:=inverse[i,k]
				inverse[i,k]:=inverse[p,k]
				inverse[p,k]:=a[k]
				k:=k+1
			end
			ensure
				trivial : n>0 and Matrix.height =n and Matrix.width=n and inverse.height=n and inverse.width=2*n and exists
					-- trivial conditions
				matrix_not_changed : Matrix = old Matrix
			rescue
         		print("INVALID")
				io.new_line
		end

	create_identity
		-- make the invverse matrix augmented
		require
			trivial : n>0 and Matrix.height =n and Matrix.width=n and inverse.height=n and inverse.width=2*n and exists
				-- trivial conditions
		local
			i:INTEGER
		do
			from
				i:=1
			invariant
				bounds : i>0 and i<=n+1
			until
				i>n
			loop
				inverse[i,i+n]:=1
				i:=i+1
			end
			ensure
				trivial : n>0 and Matrix.height =n and Matrix.width=n and inverse.height=n and inverse.width=2*n and exists
					-- trivial conditions
				matrix_not_changed : Matrix = old Matrix
			rescue
         		print("INVALID")
				io.new_line
		end

	print_inv
		-- PRINT THE INVERSE IF EXISTS
		require
			trivial : n>0 and Matrix.height =n and Matrix.width=n and inverse.height=n and inverse.width=2*n and exists
				-- trivial conditions
		local
			i:INTEGER
			j:INTEGER
		do
			from
				i:=1
			invariant
				bounds : i>0 and i<=n+1
			until
				i>n
			loop
				from
					j:=n+1
				invariant
					bounds : j>n and j<=2*n+1
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
			ensure
				trivial : n>0 and Matrix.height =n and Matrix.width=n and inverse.height=n and inverse.width=2*n and exists
					-- trivial conditions
				matrix_not_changed : Matrix = old Matrix
			rescue
         		print("INVALID")
				io.new_line
		end

	check_inverse:BOOLEAN
		-- check if AA_inverse = I
		require
			trivial : n>0 and Matrix.height =n and Matrix.width=n and inverse.height=n and inverse.width=2*n and exists
				-- trivial conditions
		local
			i,j,k:INTEGER
			identity1:ARRAY2[REAL]
			identity2:ARRAY2[REAL]
		do
			-- matrix multiplication
			create identity1.make_filled(0.0,n,n)
			create identity2.make_filled(0.0,n,n)
			Result:=true
			from
				i:=1
			invariant
				bounds:i>0 and i<=n+1
				inv_conditions : inverse.height=n and inverse.width=2*n
					--loop invariant
				identity_conditions : identity1.height=n and identity1.width=n and identity2.height=n and identity2.width=n
			until
				i>n
			loop
				from
					j:=1
				invariant
					bounds:j>0 and j<=N+1
					inv_conditions : inverse.height=n and inverse.width=2*n
						--loop invariant
					identity_conditions : identity1.height=n and identity1.width=n and identity2.height=n and identity2.width=n
				until
					j>n
				loop
					from
						k:=1
					invariant
						bounds:k>0 and k<=n+1
						inv_conditions : inverse.height=n and inverse.width=2*n
						--loop invariant
						identity_conditions : identity1.height=n and identity1.width=n and identity2.height=n and identity2.width=n
					until
						k>n
					loop
						identity1[i,j]:= identity1[i,j] + inverse[i,k+n]*Matrix[k,j]
						identity2[i,j]:= identity2[i,j] + Matrix[k,j]*inverse[i,k+n]
						k:=k+1
					end
					if (i=j and not (identity1[i,j]>=1-eps and identity1[i,j]<=1+eps )) or (i/=j and not (identity1[i,j]>=-eps and identity1[i,j]<=eps )) or (i=j and not (identity2[i,j]>=1-eps and identity2[i,j]<=1+eps )) or (i/=j and not (identity2[i,j]>=-eps and identity2[i,j]<=eps ))then
						Result:=false
						j:=n+1
					else
						j:=j+1
					end
				end
				if Result=false then
					i:=n+1
				else
					i:=i+1
				end

			end
			ensure
				trivial : n>0 and Matrix.height =n and Matrix.width=n and inverse.height=n and inverse.width=2*n and exists
					-- trivial conditions
				matrix_not_changed : Matrix = old Matrix
			rescue
				print("INVALID")
				io.new_line
		end

end
