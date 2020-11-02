echo "<<< NEXT SHOULD BE ERRORS >>>"
echo " "
echo "*1. No ants:"
./lem-in < maps/e_no_ants.map
echo " "
echo "2. Zero ants:"
./lem-in < maps/e_zero_ants.map
echo " "
echo "3. Command after start:"
./lem-in < maps/e_cmd_after_start.map
echo " "
echo "4. Command after end:"
./lem-in < maps/e_cmd_after_end.map
echo " "
echo "5. Comment after end:"
./lem-in < maps/e_cmmnt_after_end.map
echo " "
echo "6. No start room:"
./lem-in < maps/e_no_startrm.map
echo " "
echo "7. No end room:"
./lem-in < maps/e_no_endrm.map
echo " "
echo "?. No links:"
./lem-in < maps/e_no_links.map
echo " "
echo "?. No rooms:"
./lem-in < maps/e_no_rooms.map
echo " "
echo "8. No route to end:"
./lem-in < maps/e_no_route_end.map
echo " "
echo "9. No route from start:"
./lem-in < maps/e_no_route_start.map
echo " "
echo "10. Double end:" #should not print the contents of farm?
./lem-in < maps/e_double_end.map
echo " "
echo "*11. Empty map:"
./lem-in < maps/e_empty.map
echo " "
echo "*12. Non-existant map:"
./lem-in < maps/murmeli.map
echo " "
echo "?. Link is left open:" #should not print the contents of farm?
./lem-in < maps/e_open_link.map
echo " "
echo "?. Link is left open b:" #should not print the contents of farm?
./lem-in < maps/e_open_link.map
echo " "
echo "?. Link is left open (no line):" #should not print the contents of farm?
./lem-in < maps/e_open_link_no_line.map
echo " "
echo "?. Invalid link to Timbuktu:" #should not print the contents of farm?
./lem-in < maps/e_invalid_link.map
echo " "
echo "?. Letter in co-ors:" #should not print the contents of farm?
./lem-in < maps/e_letter_in_coors.map
echo " "
echo "?. Too many co-ors:" #should not print the contents of farm?
./lem-in < maps/e_too_many_coors.map
echo " "

# negatiiviset coordinaatit
# seg fault if max int of ants NOT OK
# if room names contain spaces or dashes -> input error. NOT OK
