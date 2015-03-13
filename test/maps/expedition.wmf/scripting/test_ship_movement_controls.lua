run(function()
    game.desired_speed = 30 * 1000
	p1:place_bob("ship", map:get_field(10, 10))

	port = map:get_field(16, 16).immovable
 	port:set_wares("log", 10) -- no sense to wait
	port:set_wares("blackwood", 10) 
	 
   	--getting table with all our ships (single one only)
   	ships = p1:get_ships()

	--veryfing that ship is indeed placed where should be :)
	assert_equal(10,ships[1].field.x)
	assert_equal(10,ships[1].field.y)
		 	
   	--ships table should contain 1 item (1 ship)
  	assert_equal(1, #ships)

  	--ship has no wares on it
  	assert_equal(0,ships[1]:get_wares())
  	
  	--no destination is set
  	assert(not ships[1].destination)
 
  	--ships in transport state (=0)
  	assert_equal(0,ships[1].status)

	--the  warehouse is probably not in expedition status :)
	assert(not map:get_field(8, 18).immovable.expedition_in_progress)

	--starting prepartion for expedition
	assert(not port.expedition_in_progress)
   	port:start_expedition()
   	sleep (300)
	assert(port.expedition_in_progress)   		
   	
	--ships changes status when exp ready
   	while ships[1].status == 0 do sleep(2000) end
   	
 	--sending NW and verifying
   	ships[1].scout_direction="nw"
   	sleep(6000)
  	assert_equal("nw", ships[1].scout_direction)
   	
   	while ships[1].scout_direction == "nw" do
   		sleep (2000)
   	end

	--now ships stops nearby NW coast, so sending it back
	ships[1].scout_direction="se"
	sleep(3000)
	assert_equal("se", ships[1].scout_direction)
	
	--waiting till it stops (no direction/nil is returned)
	while ships[1].scout_direction do sleep(2000) end
	
	--sending to scout the island
	ships[1].island_scout_direction="ccw";
	sleep(3000)	
	assert_equal("ccw", ships[1].island_scout_direction)
	
	--fine, now change the direction
	ships[1].island_scout_direction="cw";
	sleep(3000)	
	assert_equal("cw", ships[1].island_scout_direction)

    -- wait till it finds a port
    wait_for_message("Port Space Found")	
	--starting colonization port here
	assert(ships[1]:build_colonization_port())
	sleep(15000)
	stable_save("port_in_constr")

	-- while unfinished yet, removing it
	new_port=map:get_field(16,2).immovable
	assert(new_port)
	new_port:remove()
	sleep(3000)
	
	--yes, the ships is back in transport mode
	assert(0,ships[1].status)
	
	print("# All Tests passed.")
   	wl.ui.MapView():close()

end)
