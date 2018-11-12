note
	description: "Finding the Inverse of Matrix if exists"
	author: "Puneet Mangla (CS17BTECH11029)"

class
    APPLICATION
    	-- inverse of matrix M
create
    make
feature
       make
         local
           i,j: INTEGER
           Matrix:MATRIX
           det :REAL
	   v:REAL
           x:LIST[STRING]
           	-- local 'MATRIX' object and determinant
         do
         	io.read_integer
         	create Matrix.make(io.last_integer)
         		-- Read dimension
         	from
         		i:=1
         	invariant
         		row_range : i>0 and i<=Matrix.dimension+1
         			-- loop invariants
         	until
         		i>Matrix.dimension
         	loop
         		io.read_line
         		x:= io.last_string.split (' ')
         		from
         			j:= 1
         		invariant
         			column_range : j>0 and j<=Matrix.dimension+1
         			-- loop invariants
         		until
         			j >Matrix.dimension
         		loop
				v:= x[j].to_real
         			Matrix.mat[i,j] := v
         			j:=j+1
         		end
         		i:=i+1
         	end
         	det:= Matrix.determinant
         	 -- find determinant of matrix
         	if det=0.0 then
         		print("INVALID")
         		io.new_line
         			-- check if it is zero or not
         	else
         		Matrix.inverse(det).printMatrix
         		 -- find inverse and print
         	end
         	
         	rescue
         		print("INVALID")
				io.new_line
		end
end
