note
	description: "Class Representing Square matrix with determinant ,adjoint and inverse."
	author: "Puneet Mangla (CS17BTECH11029)"

class
	MATRIX
		-- Square Matrix Class
create
	make

feature
	N:INTEGER
		-- Dimension of the square matrix
	matrix :ARRAY2[REAL]
		-- 2D array of REAL values i.e actual matrix

feature
	make (dim:INTEGER)
		-- Intialisation of Matrix
		require
			non_negative_dimension : dim>0
				-- require positive dimension
		do
			N:=dim
			create matrix.make_filled(0.0,dim,dim)

			ensure
				height_dimension : matrix.height=N
				width_dimension : matrix.width =N
					-- check if dimensions of matrix are same i.e is it square?
			rescue
				print("INVALID")
				io.new_line
		end

	mat:ARRAY2[REAL]
		-- returns refrence to 'matrix' attribute
		require
			dimensions : N>0 and matrix.height=N and matrix.width=N
				-- checking existence of matrix and its square nature
		do
			create Result.make_filled(0.0,N,N)
			Result:=matrix
			ensure
				result_check : Result.height=N and Result.width=N
					-- result check validity
				dimensions : N>0 and matrix.height=N and matrix.width=N
				matrix_not_changed : matrix = old matrix
			rescue
				print("INVALID")
				io.new_line
		end

	dimension:INTEGER
		-- returns dimension of the square matrix
		require
			dimensions : N>0 and matrix.height=N and matrix.width=N
				-- checking existence of matrix and its square nature
		do
			Result:=N
			ensure
				dimensions : N>0 and matrix.height=N and matrix.width=N
				matrix_not_changed : matrix = old matrix
					-- checking existence of matrix and its square nature
			rescue
				print("INVALID")
				io.new_line
		end

	printMatrix
		-- Print 'MATRIX' object in standard form
		require
			dimensions : N>0 and matrix.height=N and matrix.width=N
				-- checking existence of matrix and its square nature
		local
           i,j : INTEGER
         do
         	from
         		i:=1
         	invariant
         		row_range : i>0 and i<=N+1
         			-- loop invariants
         	until
         		i>N
         	loop
         		from
         			j:= 1
         		invariant
         			column_range : j>0 and j<=N+1
         				-- loop invariants
         		until
         			j>N
         		loop
         			if matrix[i,j]=-0.0 then
         				print("0")
         			else
         				print(matrix[i,j])
         			end
         			print(" ")
         			j:=j+1
         		end
         		io.new_line
         		i:=i+1
         	end
         	ensure
				dimensions : N>0 and matrix.height=N and matrix.width=N
				matrix_not_changed : matrix = old matrix
					-- checking existence of matrix and its square nature
			rescue
				print("INVALID")
				io.new_line
		end

	determinant:REAL
		-- returns determinant of 'MATRIX' object
		-- recursive program
		require
			dimensions : N>0 and matrix.height=N and matrix.width=N
				-- checking existence of matrix and its square nature
		local
			j:INTEGER
		do
			Result:=0.0
			if N=1 then
				Result:= matrix[1,1]
			else
					from
						j:=1
					invariant
						coulumn_range: j>0 and j<=N+1
							-- loop invariants
					until
						j>N
					loop
						if j\\2 =1 then
							Result:= Result + matrix[1,j]*(cofactor(1,j).determinant)
						else
							Result:= Result  - matrix[1,j]*(cofactor(1,j).determinant)
						end
						j:=j+1
					end
			end
			ensure
				dimensions : N>0 and matrix.height=N and matrix.width=N
				matrix_not_changed : matrix = old matrix
					-- checking existence of matrix and its square nature
			rescue
				print("INVALID")
				io.new_line
		end

	cofactor(row,column:INTEGER): MATRIX
		-- returns cofactor 'MATRIX' Object of (row,column) cell
		require
				bounds : row>0 and row<=N and column>0 and column<=N
					-- check if cell is valid
				dimensions : N>0 and matrix.height=N and matrix.width=N
					-- checking existence of matrix and its square nature
		local
			i,j,k,l:INTEGER
		do
			k:=1
			l:=1
			if N=1 then
				create Result.make (1)
				Result.mat[1,1]:=1
			else
				create Result.make(N-1)
				from
					i:=1
				invariant
         			row_range : i>0 and i<=N+1
         			k_l_range : k>0 and k<=N and l>0 and l<=N
         			result_check : (Result.dimension=N-1 or Result.dimension=1)
         				-- loop invariants

				until
					i>N
				loop
					from
						j:=1
					invariant
         				column_range : j>0 and j<=N+1
         				k_l_range : k>0 and k<=N and l>0 and l<=N
         				result_check : (Result.dimension=N-1 or Result.dimension=1)
         					-- loop invariants

					until
						j>N
					loop
						if i/=row and j/=column then
							Result.mat[k,l]:=matrix[i,j]
							l:=l+1
							if l=N then
								l:=1
								k:=k+1
							end
						end
						j:=j+1
					end
					i:=i+1
				end
			end
			ensure
				bounds : row>0 and row<=N and column>0 and column<=N
				result_check : (Result.dimension=N-1 or Result.dimension=1)
					-- ensure validity of arguments and results
				dimensions : N>0 and matrix.height=N and matrix.width=N
					-- checking existence of matrix and its square nature
				matrix_not_changed : matrix = old matrix
					-- checking existence of matrix and its square nature
			rescue
				print("INVALID")
				io.new_line
		end

	adjoint:MATRIX
		-- Adjoint of matrix using cofactors and determinant
		require
			dimensions : N>0 and matrix.height=N and matrix.width=N
				-- checking existence of matrix and its square nature
		local
			i,j:INTEGER
		do
			create Result.make(N)
			from
				i:=1
			invariant
         			row_range : i>0 and i<=N+1
         			result_check : Result.dimension=N
				 		-- result validity
         				-- loop invariants
			until
				i>N
			loop
				from
					j:=1
				invariant
         				column_range : j>0 and j<=N+1
         				result_check : Result.dimension=N
				 			-- result validity
         					-- loop invariants
				until
					j>N
				loop
					if (i+j)\\2=0 then
						Result.mat[j,i]:= cofactor(i,j).determinant
					else
						Result.mat[j,i]:= -cofactor(i,j).determinant
					end
					j:=j+1
				end
				i:=i+1
			end
			ensure
				result_check : Result.dimension=N
				 	-- result validity
				dimensions : N>0 and matrix.height=N and matrix.width=N
					-- checking existence of matrix and its square nature
				matrix_not_changed : matrix = old matrix
					-- checking existence of matrix and its square nature
			rescue
				print("INVALID")
				io.new_line
		end

	inverse (det:REAL) : MATRIX
		-- Inverse of matrix
			require
				non_zero_determinant : det/=0
					-- check if det is zero or not
				dimensions : N>0 and matrix.height=N and matrix.width=N
			local
				i,j:INTEGER
			do
				create Result.make(N)
				Result:=adjoint
				from
					i:=1
				invariant
         				column_range : i>0 and i<=N+1
         				result_check : Result.dimension=N
							-- result is valid
         					-- loop invariants
				until
					i>N
				loop
					from
						j:=1
					invariant
         				column_range : j>0 and j<=N+1
         				result_check : Result.dimension=N
							-- result is valid
         					-- loop invariants
					until
						j>N
					loop
						Result.mat[i,j]:= Result.mat[i,j]/det
						j:=j+1
					end
					i:=i+1
				end
				ensure
						det_not_changed : det = old det
						result_check : Result.dimension=N
							-- check if det is same or not and result is valid
						dimensions : N>0 and matrix.height=N and matrix.width=N
							-- checking existence of matrix and its square nature
						matrix_not_changed : matrix = old matrix
							-- checking existence of matrix and its square nature
						identity_check : check_inverse(Result)=true
							-- check if AA_inverse = I
				rescue
				print("INVALID")
				io.new_line
			end

	check_inverse(inv:MATRIX):BOOLEAN
		-- check if AA_inverse = I
		require
			dimensions : N>0 and matrix.height=N and matrix.width=N
			inv_conditions : inv.dimension=N
				-- trivial conditions
		local
			i,j,k:INTEGER
			identity1:MATRIX
			identity2:MATRIX
		do
			-- matrix multiplication
			create identity1.make (N)
			create identity2.make (N)
			Result:=true
			from
				i:=1
			invariant
				bounds:i>0 and i<=N+1
				inv_conditions : inv.dimension=N
					--loop invariant
				identity_conditions : identity1.dimension=N and identity2.dimension=N
			until
				i>N
			loop
				from
					j:=1
				invariant
					bounds:j>0 and j<=N+1
					inv_conditions : inv.dimension=N
					identity_conditions : identity1.dimension=N and identity2.dimension=N
				until
					j>N
				loop
					from
						k:=1
					invariant
						bounds:k>0 and k<=N+1
						inv_conditions : inv.dimension=N
						identity_conditions : identity1.dimension=N and identity2.dimension=N
					until
						k>N
					loop
						identity1.mat[i,j]:= identity1.mat[i,j] + inv.mat[i,k]*matrix[k,j]
						identity2.mat[i,j]:= identity2.mat[i,j] + matrix[k,j]*inv.mat[i,k]
						k:=k+1
					end
					if (i=j and identity1.mat[i,j]/=1.0) or (i/=j and identity1.mat[i,j]/=0.0) or (i=j and identity2.mat[i,j]/=1.0) or (i/=j and identity2.mat[i,j]/=0.0)then
						Result:=false
						j:=N+1
					else
						j:=j+1
					end
				end
				if Result=false then
					i:=N+1
				else
					i:=i+1
				end

			end
			ensure
				inv_conditions : inv.dimension=N and inv=old inv
				dimensions : N>0 and matrix.height=N and matrix.width=N
					-- checking existence of matrix and its square nature
				matrix_not_changed : matrix = old matrix
					-- checking existence of matrix and its square nature
			rescue
				print("INVALID")
				io.new_line
		end

	invariant
		non_void_matrix : matrix/=Void
		dimension : N>0
		square_matrix : matrix.height=N and matrix.width=N
			-- Class Invariants
end
