SELECT people.name
FROM people
WHERE people.id IN
(SELECT stars.person_id
FROM stars
WHERE stars.movie_id IN
(SELECT movies.id
FROM movies
JOIN stars
ON movies.id = stars.movie_id
JOIN people
ON stars.person_id = people.id
WHERE people.name = 'Kevin Bacon' AND people.birth = 1958))
	AND NOT people.name = 'Kevin Bacon';