defmodule First do

def printname(name) do
	case name do
		"ram" -> :yes
		_ -> :no
	end
end
end
