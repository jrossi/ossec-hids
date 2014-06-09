

function adder(T) 
  for key,value in pairs(T) do print(key,value) end

end

function deleter(T)
  print("---LUA: delete -> LUA")
  print("---LUA: deleter user:"..T.user.." ipaddr:"..T.ipaddr)
end

function timer(...)
  print("running timer")
  print(...)
end

function init()
  print("---LUA: starting lua init")
  print("---LUA: ending lua init")
end

ar.register_add(adder)
ar.register_timer(5, timer)
ar.register_delete(deleter)
ar.register_init(init)

