# Write your MySQL query statement below
select artist, count(id) as occurrences from Spotify group by artist order by occurrences desc, artist;