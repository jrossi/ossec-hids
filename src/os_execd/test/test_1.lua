
print("---LUA: lua starting")

function adder(T) 
  print("---LUA: adder -> LUA")
  for key,value in pairs(T) do print(key,value) end

end

function deleter(user, ipaddr)
  print("---LUA: delete -> LUA")
  print("---LUA: deleter user:"..user.." ipaddr:"..ipaddr)
end

function init()
  print("---LUA: starting lua init")
  print("---LUA: ending lua init")
end

ar.register_add(adder)
ar.register_delete(deleter)
ar.register_init(init)

