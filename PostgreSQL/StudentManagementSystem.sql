--
-- PostgreSQL database dump
--

-- Dumped from database version 9.5.14
-- Dumped by pg_dump version 9.5.14

SET statement_timeout = 0;
SET lock_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


--
-- Name: createtrimesternotable(text); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION public.createtrimesternotable(trimesterno text) RETURNS void
    LANGUAGE plpgsql
    AS $$

    BEGIN

    EXECUTE format

    (

      '

        CREATE TABLE IF NOT EXISTS %I 

        (

		"courseCode" text NOT NULL primary key,

		"courseName" text NOT NULL,

		"creditHour" integer NOT NULL,

		"preRequisite" text,

		"academicianInCharge" text NOT NULL,	

		"isOpen" boolean NOT NULL,

		"courseVenue" text NOT NULL,

		"courseTime" text NOT NULL,

		"courseFaculty" text NOT NULL,

		"courseProgram" text NOT NULL,

		"courseOfferedYear" text NOT NULL,

		"courseOfferedTrimester" text NOT NULL DEFAULT ''1''::text,



		

		FOREIGN KEY ("academicianInCharge") REFERENCES public."User" ("userID") MATCH SIMPLE

				ON UPDATE NO ACTION ON DELETE NO ACTION,

		FOREIGN KEY ("courseFaculty") REFERENCES public."Faculty" ("facultyName") MATCH SIMPLE

				ON UPDATE NO ACTION ON DELETE NO ACTION,

		FOREIGN KEY ("courseOfferedYear") REFERENCES public."Trimester" (trimester) MATCH SIMPLE

				ON UPDATE NO ACTION ON DELETE NO ACTION

	);

      ',

      trimesterno

    );

  END;

  $$;


ALTER FUNCTION public.createtrimesternotable(trimesterno text) OWNER TO postgres;

--
-- Name: createtrimestertable(text); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION public.createtrimestertable(trimester text) RETURNS void
    LANGUAGE plpgsql
    AS $$

    BEGIN

    EXECUTE format

    (

      '

        CREATE TABLE IF NOT EXISTS %I 

        (

		"trimesterNo" text NOT NULL primary key,

		"trimesterYear" text NOT NULL,

		status text,

		"isOpen" boolean NOT NULL,

		FOREIGN KEY ("trimesterYear") REFERENCES public."Trimester" (trimester) MATCH SIMPLE

		ON UPDATE NO ACTION ON DELETE NO ACTION

	);

      ',

      trimester

    );

  END;

  $$;


ALTER FUNCTION public.createtrimestertable(trimester text) OWNER TO postgres;

--
-- Name: createusertable(text); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION public.createusertable(userid text) RETURNS void
    LANGUAGE plpgsql
    AS $$

    BEGIN

    EXECUTE format

    (

      '

	CREATE TABLE IF NOT EXISTS %I

        (

		"courseCode" text NOT NULL,

		"courseOfferedYear" text NOT NULL,

		"courseOfferedTrimester" text NOT NULL,

		PRIMARY KEY ("courseCode"),

		FOREIGN KEY ("courseOfferedYear") REFERENCES public."Trimester" (trimester) MATCH SIMPLE

		ON UPDATE NO ACTION ON DELETE NO ACTION

	);

      ',

      userid

    );

  END;

  $$;


ALTER FUNCTION public.createusertable(userid text) OWNER TO postgres;

--
-- Name: createusertrimestertaken(text); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION public.createusertrimestertaken(userid text) RETURNS void
    LANGUAGE plpgsql
    AS $$

    BEGIN

    EXECUTE format

    (

      '

	CREATE TABLE IF NOT EXISTS %I

        (

		trimester text NOT NULL,

		

		PRIMARY KEY (trimester)

		

	);

      ',

      userid

    );

  END;

  $$;


ALTER FUNCTION public.createusertrimestertaken(userid text) OWNER TO postgres;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: 1151302123; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."1151302123" (
    "courseCode" text NOT NULL,
    "courseOfferedYear" text NOT NULL,
    "courseOfferedTrimester" text NOT NULL
);


ALTER TABLE public."1151302123" OWNER TO postgres;

--
-- Name: 1151302123trimesterTaken; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."1151302123trimesterTaken" (
    trimester text NOT NULL
);


ALTER TABLE public."1151302123trimesterTaken" OWNER TO postgres;

--
-- Name: 1161301595; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."1161301595" (
    "courseCode" text NOT NULL,
    "courseOfferedYear" text NOT NULL,
    "courseOfferedTrimester" text NOT NULL
);


ALTER TABLE public."1161301595" OWNER TO postgres;

--
-- Name: 1161301595trimesterTaken; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."1161301595trimesterTaken" (
    trimester text NOT NULL
);


ALTER TABLE public."1161301595trimesterTaken" OWNER TO postgres;

--
-- Name: 1161302847; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."1161302847" (
    "courseCode" text NOT NULL,
    "courseOfferedYear" text NOT NULL,
    "courseOfferedTrimester" text NOT NULL
);


ALTER TABLE public."1161302847" OWNER TO postgres;

--
-- Name: 1161302847trimesterTaken; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."1161302847trimesterTaken" (
    trimester text NOT NULL
);


ALTER TABLE public."1161302847trimesterTaken" OWNER TO postgres;

--
-- Name: 1161303847; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."1161303847" (
    "courseCode" text NOT NULL,
    "courseOfferedYear" text NOT NULL,
    "courseOfferedTrimester" text NOT NULL
);


ALTER TABLE public."1161303847" OWNER TO postgres;

--
-- Name: 1161303847trimesterTaken; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."1161303847trimesterTaken" (
    trimester text NOT NULL
);


ALTER TABLE public."1161303847trimesterTaken" OWNER TO postgres;

--
-- Name: 1161303848; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."1161303848" (
    "courseCode" text NOT NULL,
    "courseOfferedYear" text NOT NULL,
    "courseOfferedTrimester" text NOT NULL
);


ALTER TABLE public."1161303848" OWNER TO postgres;

--
-- Name: 1161303848trimesterTaken; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."1161303848trimesterTaken" (
    trimester text NOT NULL
);


ALTER TABLE public."1161303848trimesterTaken" OWNER TO postgres;

--
-- Name: 1171300038; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."1171300038" (
    "courseCode" text NOT NULL,
    "courseOfferedYear" text NOT NULL,
    "courseOfferedTrimester" text NOT NULL
);


ALTER TABLE public."1171300038" OWNER TO postgres;

--
-- Name: 1171300038trimesterTaken; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."1171300038trimesterTaken" (
    trimester text NOT NULL
);


ALTER TABLE public."1171300038trimesterTaken" OWNER TO postgres;

--
-- Name: 1171500058; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."1171500058" (
    "courseCode" text NOT NULL,
    "courseOfferedYear" text NOT NULL,
    "courseOfferedTrimester" text NOT NULL
);


ALTER TABLE public."1171500058" OWNER TO postgres;

--
-- Name: 1171500058trimesterTaken; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."1171500058trimesterTaken" (
    trimester text NOT NULL
);


ALTER TABLE public."1171500058trimesterTaken" OWNER TO postgres;

--
-- Name: 17/18; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."17/18" (
    "trimesterNo" text NOT NULL,
    "trimesterYear" text NOT NULL,
    status text,
    "isOpen" boolean NOT NULL
);


ALTER TABLE public."17/18" OWNER TO postgres;

--
-- Name: 17/18-1; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."17/18-1" (
    "courseCode" text NOT NULL,
    "courseName" text NOT NULL,
    "creditHour" integer NOT NULL,
    "preRequisite" text,
    "academicianInCharge" text NOT NULL,
    "isOpen" boolean NOT NULL,
    "courseVenue" text NOT NULL,
    "courseTime" text NOT NULL,
    "courseFaculty" text NOT NULL,
    "courseProgram" text NOT NULL,
    "courseOfferedYear" text NOT NULL,
    "courseOfferedTrimester" text DEFAULT '1'::text NOT NULL
);


ALTER TABLE public."17/18-1" OWNER TO postgres;

--
-- Name: 17/18-2; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."17/18-2" (
    "courseCode" text NOT NULL,
    "courseName" text NOT NULL,
    "creditHour" integer NOT NULL,
    "preRequisite" text,
    "academicianInCharge" text NOT NULL,
    "isOpen" boolean NOT NULL,
    "courseVenue" text NOT NULL,
    "courseTime" text NOT NULL,
    "courseFaculty" text NOT NULL,
    "courseProgram" text NOT NULL,
    "courseOfferedYear" text NOT NULL,
    "courseOfferedTrimester" text DEFAULT '2'::text NOT NULL
);


ALTER TABLE public."17/18-2" OWNER TO postgres;

--
-- Name: 17/18-3; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."17/18-3" (
    "courseCode" text NOT NULL,
    "courseName" text NOT NULL,
    "creditHour" integer NOT NULL,
    "preRequisite" text,
    "academicianInCharge" text NOT NULL,
    "isOpen" boolean NOT NULL,
    "courseVenue" text NOT NULL,
    "courseTime" text NOT NULL,
    "courseFaculty" text NOT NULL,
    "courseProgram" text NOT NULL,
    "courseOfferedYear" text NOT NULL,
    "courseOfferedTrimester" text DEFAULT '3'::text NOT NULL
);


ALTER TABLE public."17/18-3" OWNER TO postgres;

--
-- Name: 18/19; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."18/19" (
    "trimesterNo" text NOT NULL,
    "trimesterYear" text NOT NULL,
    status text,
    "isOpen" boolean NOT NULL
);


ALTER TABLE public."18/19" OWNER TO postgres;

--
-- Name: 18/19-1; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."18/19-1" (
    "courseCode" text NOT NULL,
    "courseName" text NOT NULL,
    "creditHour" integer NOT NULL,
    "preRequisite" text,
    "academicianInCharge" text NOT NULL,
    "isOpen" boolean NOT NULL,
    "courseVenue" text NOT NULL,
    "courseTime" text NOT NULL,
    "courseFaculty" text NOT NULL,
    "courseProgram" text NOT NULL,
    "courseOfferedYear" text NOT NULL,
    "courseOfferedTrimester" text DEFAULT '1'::text NOT NULL
);


ALTER TABLE public."18/19-1" OWNER TO postgres;

--
-- Name: Faculty; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."Faculty" (
    "facultyName" text NOT NULL,
    "facultyFullName" text NOT NULL
);


ALTER TABLE public."Faculty" OWNER TO postgres;

--
-- Name: Trimester; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."Trimester" (
    trimester text NOT NULL
);


ALTER TABLE public."Trimester" OWNER TO postgres;

--
-- Name: User; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."User" (
    "userID" text NOT NULL,
    "userName" text NOT NULL,
    "userPassword" text NOT NULL,
    "userGender" "char",
    "facultyName" text,
    "userType" text NOT NULL
);


ALTER TABLE public."User" OWNER TO postgres;

--
-- Data for Name: 1151302123; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."1151302123" ("courseCode", "courseOfferedYear", "courseOfferedTrimester") FROM stdin;
\.


--
-- Data for Name: 1151302123trimesterTaken; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."1151302123trimesterTaken" (trimester) FROM stdin;
17/18-2
\.


--
-- Data for Name: 1161301595; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."1161301595" ("courseCode", "courseOfferedYear", "courseOfferedTrimester") FROM stdin;
BPS1014	17/18	2
\.


--
-- Data for Name: 1161301595trimesterTaken; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."1161301595trimesterTaken" (trimester) FROM stdin;
17/18-2
\.


--
-- Data for Name: 1161302847; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."1161302847" ("courseCode", "courseOfferedYear", "courseOfferedTrimester") FROM stdin;
\.


--
-- Data for Name: 1161302847trimesterTaken; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."1161302847trimesterTaken" (trimester) FROM stdin;
17/18-2
\.


--
-- Data for Name: 1161303847; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."1161303847" ("courseCode", "courseOfferedYear", "courseOfferedTrimester") FROM stdin;
TCP1101	17/18	1
TPT1101	17/18	1
TMA1101	17/18	1
TMA1201	17/18	2
TIS1101	17/18	2
\.


--
-- Data for Name: 1161303847trimesterTaken; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."1161303847trimesterTaken" (trimester) FROM stdin;
17/18-1
17/18-2
17/18-3
\.


--
-- Data for Name: 1161303848; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."1161303848" ("courseCode", "courseOfferedYear", "courseOfferedTrimester") FROM stdin;
TIS1101	17/18	2
\.


--
-- Data for Name: 1161303848trimesterTaken; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."1161303848trimesterTaken" (trimester) FROM stdin;
17/18-2
\.


--
-- Data for Name: 1171300038; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."1171300038" ("courseCode", "courseOfferedYear", "courseOfferedTrimester") FROM stdin;
TIS1101	17/18	2
TCP1101	17/18	2
TPT1101	17/18	2
\.


--
-- Data for Name: 1171300038trimesterTaken; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."1171300038trimesterTaken" (trimester) FROM stdin;
17/18-2
\.


--
-- Data for Name: 1171500058; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."1171500058" ("courseCode", "courseOfferedYear", "courseOfferedTrimester") FROM stdin;
\.


--
-- Data for Name: 1171500058trimesterTaken; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."1171500058trimesterTaken" (trimester) FROM stdin;
17/18-2
\.


--
-- Data for Name: 17/18; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."17/18" ("trimesterNo", "trimesterYear", status, "isOpen") FROM stdin;
3	17/18	upcoming	f
1	17/18	inactive	f
2	17/18	active	t
\.


--
-- Data for Name: 17/18-1; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."17/18-1" ("courseCode", "courseName", "creditHour", "preRequisite", "academicianInCharge", "isOpen", "courseVenue", "courseTime", "courseFaculty", "courseProgram", "courseOfferedYear", "courseOfferedTrimester") FROM stdin;
TMA1101	Calculus	4	\N	acad2	f	1	1	FCI	UnderGraduate	17/18	1
TCP1101	Programming Fundumentals	4	\N	acad	f	1	1	FCI	UnderGraduate	17/18	1
TPT1101	Professional Development	4	\N	acad	f	4	4	FCI	UnderGraduate	17/18	1
TCP1201	OOPDS	4	TCP1101	acad	f	2 	2 	FCI	UnderGraduate	17/18	1
xyz	xyz	4	\N	acad2	f	1	1	FCI	UnderGraduate	17/18	1
\.


--
-- Data for Name: 17/18-2; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."17/18-2" ("courseCode", "courseName", "creditHour", "preRequisite", "academicianInCharge", "isOpen", "courseVenue", "courseTime", "courseFaculty", "courseProgram", "courseOfferedYear", "courseOfferedTrimester") FROM stdin;
TCP1201	OOPDS	4	TCP1101	acad2	t	CQCR2001	11-13	FCI	UnderGraduate	17/18	2
TIS1101	Database Fundamentals	4	\N	acad	t	CQCR2001	4-6	FCI	UnderGraduate	17/18	2
prqstTest	PreRequisiteTest	4	xyz	acad2	t	CQCR2005	1-2	FCI	UnderGraduate	17/18	2
PGCTest	Post Graduate Course Test	4	\N	acad1	t	Test	2-4	FOM	PostGraduate	17/18	2
TCP1101	Programming Fundamentals	4	\N	acad2	t	CQCR3001	2-4	FCI	UnderGraduate	17/18	2
TMA1201	Discrete Mathmatics	4	TMA1101	acad	f	CQCR2004	2-4	FCI	UnderGraduate	17/18	2
BPB2034	PROGRAMMING F0R BUSINESS APPLICATION	3	\N	acadNur	f	CLCR3044	10-12	FOM	UnderGraduate	17/18	2
BPS1014	PSYCHOLOGY	3	\N	acadNur	f	CLCR3044	9-10	FOM	UnderGraduate	17/18	2
TPT1101	Professional Development	4	\N	acad	t	CQCR3002	4-6	FCI	UnderGraduate	17/18	2
DIPLOMATEST	Diploma Test 	4	\N	acad	f	Test	Test	FCI	Diploma	17/18	2
\.


--
-- Data for Name: 17/18-3; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."17/18-3" ("courseCode", "courseName", "creditHour", "preRequisite", "academicianInCharge", "isOpen", "courseVenue", "courseTime", "courseFaculty", "courseProgram", "courseOfferedYear", "courseOfferedTrimester") FROM stdin;
TMA1101	Calculus	4	\N	acad2	t	1	1	FCI	UnderGraduate	17/18	3
TCP1201	OOPDS	4	TCP1101	acad2	t	2 	2 	FCI	UnderGraduate	17/18	3
TPT1101	Professional Development	4	\N	acad	f	1	1	FCI	UnderGraduate	17/18	3
\.


--
-- Data for Name: 18/19; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."18/19" ("trimesterNo", "trimesterYear", status, "isOpen") FROM stdin;
1	18/19	null	f
\.


--
-- Data for Name: 18/19-1; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."18/19-1" ("courseCode", "courseName", "creditHour", "preRequisite", "academicianInCharge", "isOpen", "courseVenue", "courseTime", "courseFaculty", "courseProgram", "courseOfferedYear", "courseOfferedTrimester") FROM stdin;
\.


--
-- Data for Name: Faculty; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."Faculty" ("facultyName", "facultyFullName") FROM stdin;
FAC	Faculty Of Applied Communication
FCI	Faculty Of Computer and Informatics
FCM	Faculty Of Creative Multimedia
FOM	Faculty Of Management
FOE	Faculty Of Engineering
\.


--
-- Data for Name: Trimester; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."Trimester" (trimester) FROM stdin;
18/19
17/18
18/192
17/192
17/182
12/132
18/193
17/193
\.


--
-- Data for Name: User; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."User" ("userID", "userName", "userPassword", "userGender", "facultyName", "userType") FROM stdin;
1171500058	Imtiaz Sheik	1234	m	FCI	Diploma
acad	Rakin	1234	m	FCI	Academician
acad1	Helena	1234	f	FOM	Academician
acad2	Lim	1234	f	FCI	Academician
admin	Rakin	1234	m	\N	Admin
1151302123	Sadman Sakib	1234	m	FOE	UnderGraduate
1161303847	Mubdiul Hossain	1234	m	FCI	UnderGraduate
1161302847	Some Name	1234	m	FOM	PostGraduate
acad3	Shamsul Alam	1234	m	FOE	Academician
1161303848	Irtiza Hasan	1234	m	FCI	UnderGraduate
1171300038	Khaleduzzaman	12345	m	FCI	UnderGraduate
1161301595	Niaz Parvez	123456789	m	FOM	UnderGraduate
acadNur	Nur Azlin	1234	m	FOM	Academician
\.


--
-- Name: 1151302123_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."1151302123"
    ADD CONSTRAINT "1151302123_pkey" PRIMARY KEY ("courseCode");


--
-- Name: 1151302123trimesterTaken_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."1151302123trimesterTaken"
    ADD CONSTRAINT "1151302123trimesterTaken_pkey" PRIMARY KEY (trimester);


--
-- Name: 1161301595_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."1161301595"
    ADD CONSTRAINT "1161301595_pkey" PRIMARY KEY ("courseCode");


--
-- Name: 1161301595trimesterTaken_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."1161301595trimesterTaken"
    ADD CONSTRAINT "1161301595trimesterTaken_pkey" PRIMARY KEY (trimester);


--
-- Name: 1161302847_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."1161302847"
    ADD CONSTRAINT "1161302847_pkey" PRIMARY KEY ("courseCode");


--
-- Name: 1161302847trimesterTaken_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."1161302847trimesterTaken"
    ADD CONSTRAINT "1161302847trimesterTaken_pkey" PRIMARY KEY (trimester);


--
-- Name: 1161303847_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."1161303847"
    ADD CONSTRAINT "1161303847_pkey" PRIMARY KEY ("courseCode");


--
-- Name: 1161303847trimesterTaken_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."1161303847trimesterTaken"
    ADD CONSTRAINT "1161303847trimesterTaken_pkey" PRIMARY KEY (trimester);


--
-- Name: 1161303848_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."1161303848"
    ADD CONSTRAINT "1161303848_pkey" PRIMARY KEY ("courseCode");


--
-- Name: 1161303848trimesterTaken_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."1161303848trimesterTaken"
    ADD CONSTRAINT "1161303848trimesterTaken_pkey" PRIMARY KEY (trimester);


--
-- Name: 1171300038_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."1171300038"
    ADD CONSTRAINT "1171300038_pkey" PRIMARY KEY ("courseCode");


--
-- Name: 1171300038trimesterTaken_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."1171300038trimesterTaken"
    ADD CONSTRAINT "1171300038trimesterTaken_pkey" PRIMARY KEY (trimester);


--
-- Name: 1171500058_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."1171500058"
    ADD CONSTRAINT "1171500058_pkey" PRIMARY KEY ("courseCode");


--
-- Name: 1171500058trimesterTaken_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."1171500058trimesterTaken"
    ADD CONSTRAINT "1171500058trimesterTaken_pkey" PRIMARY KEY (trimester);


--
-- Name: 17/18-1_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."17/18-1"
    ADD CONSTRAINT "17/18-1_pkey" PRIMARY KEY ("courseCode");


--
-- Name: 17/18-2_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."17/18-2"
    ADD CONSTRAINT "17/18-2_pkey" PRIMARY KEY ("courseCode");


--
-- Name: 17/18-3_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."17/18-3"
    ADD CONSTRAINT "17/18-3_pkey" PRIMARY KEY ("courseCode");


--
-- Name: 17/18_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."17/18"
    ADD CONSTRAINT "17/18_pkey" PRIMARY KEY ("trimesterNo");


--
-- Name: 18/19-1_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."18/19-1"
    ADD CONSTRAINT "18/19-1_pkey" PRIMARY KEY ("courseCode");


--
-- Name: 18/19_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."18/19"
    ADD CONSTRAINT "18/19_pkey" PRIMARY KEY ("trimesterNo");


--
-- Name: Trimester_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Trimester"
    ADD CONSTRAINT "Trimester_pkey" PRIMARY KEY (trimester);


--
-- Name: User_userID_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."User"
    ADD CONSTRAINT "User_userID_key" UNIQUE ("userID");


--
-- Name: facultyName; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Faculty"
    ADD CONSTRAINT "facultyName" PRIMARY KEY ("facultyName");


--
-- Name: userID; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."User"
    ADD CONSTRAINT "userID" PRIMARY KEY ("userID");


--
-- Name: 1151302123_courseOfferedYear_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."1151302123"
    ADD CONSTRAINT "1151302123_courseOfferedYear_fkey" FOREIGN KEY ("courseOfferedYear") REFERENCES public."Trimester"(trimester);


--
-- Name: 1161301595_courseOfferedYear_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."1161301595"
    ADD CONSTRAINT "1161301595_courseOfferedYear_fkey" FOREIGN KEY ("courseOfferedYear") REFERENCES public."Trimester"(trimester);


--
-- Name: 1161302847_courseOfferedYear_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."1161302847"
    ADD CONSTRAINT "1161302847_courseOfferedYear_fkey" FOREIGN KEY ("courseOfferedYear") REFERENCES public."Trimester"(trimester);


--
-- Name: 1161303847_courseOfferedYear_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."1161303847"
    ADD CONSTRAINT "1161303847_courseOfferedYear_fkey" FOREIGN KEY ("courseOfferedYear") REFERENCES public."Trimester"(trimester);


--
-- Name: 1161303848_courseOfferedYear_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."1161303848"
    ADD CONSTRAINT "1161303848_courseOfferedYear_fkey" FOREIGN KEY ("courseOfferedYear") REFERENCES public."Trimester"(trimester);


--
-- Name: 1171300038_courseOfferedYear_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."1171300038"
    ADD CONSTRAINT "1171300038_courseOfferedYear_fkey" FOREIGN KEY ("courseOfferedYear") REFERENCES public."Trimester"(trimester);


--
-- Name: 1171500058_courseOfferedYear_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."1171500058"
    ADD CONSTRAINT "1171500058_courseOfferedYear_fkey" FOREIGN KEY ("courseOfferedYear") REFERENCES public."Trimester"(trimester);


--
-- Name: 17/18-1_academicianInCharge_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."17/18-1"
    ADD CONSTRAINT "17/18-1_academicianInCharge_fkey" FOREIGN KEY ("academicianInCharge") REFERENCES public."User"("userID");


--
-- Name: 17/18-1_courseFaculty_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."17/18-1"
    ADD CONSTRAINT "17/18-1_courseFaculty_fkey" FOREIGN KEY ("courseFaculty") REFERENCES public."Faculty"("facultyName");


--
-- Name: 17/18-1_courseOfferedYear_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."17/18-1"
    ADD CONSTRAINT "17/18-1_courseOfferedYear_fkey" FOREIGN KEY ("courseOfferedYear") REFERENCES public."Trimester"(trimester);


--
-- Name: 17/18-2_academicianInCharge_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."17/18-2"
    ADD CONSTRAINT "17/18-2_academicianInCharge_fkey" FOREIGN KEY ("academicianInCharge") REFERENCES public."User"("userID");


--
-- Name: 17/18-2_courseFaculty_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."17/18-2"
    ADD CONSTRAINT "17/18-2_courseFaculty_fkey" FOREIGN KEY ("courseFaculty") REFERENCES public."Faculty"("facultyName");


--
-- Name: 17/18-3_academicianInCharge_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."17/18-3"
    ADD CONSTRAINT "17/18-3_academicianInCharge_fkey" FOREIGN KEY ("academicianInCharge") REFERENCES public."User"("userID");


--
-- Name: 17/18-3_courseFaculty_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."17/18-3"
    ADD CONSTRAINT "17/18-3_courseFaculty_fkey" FOREIGN KEY ("courseFaculty") REFERENCES public."Faculty"("facultyName");


--
-- Name: 17/18-3_courseOfferedYear_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."17/18-3"
    ADD CONSTRAINT "17/18-3_courseOfferedYear_fkey" FOREIGN KEY ("courseOfferedYear") REFERENCES public."Trimester"(trimester);


--
-- Name: 17/18_trimesterYear_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."17/18"
    ADD CONSTRAINT "17/18_trimesterYear_fkey" FOREIGN KEY ("trimesterYear") REFERENCES public."Trimester"(trimester);


--
-- Name: 18/19-1_academicianInCharge_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."18/19-1"
    ADD CONSTRAINT "18/19-1_academicianInCharge_fkey" FOREIGN KEY ("academicianInCharge") REFERENCES public."User"("userID");


--
-- Name: 18/19-1_courseFaculty_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."18/19-1"
    ADD CONSTRAINT "18/19-1_courseFaculty_fkey" FOREIGN KEY ("courseFaculty") REFERENCES public."Faculty"("facultyName");


--
-- Name: 18/19-1_courseOfferedYear_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."18/19-1"
    ADD CONSTRAINT "18/19-1_courseOfferedYear_fkey" FOREIGN KEY ("courseOfferedYear") REFERENCES public."Trimester"(trimester);


--
-- Name: 18/19_trimesterYear_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."18/19"
    ADD CONSTRAINT "18/19_trimesterYear_fkey" FOREIGN KEY ("trimesterYear") REFERENCES public."Trimester"(trimester);


--
-- Name: User_facultyName_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."User"
    ADD CONSTRAINT "User_facultyName_fkey" FOREIGN KEY ("facultyName") REFERENCES public."Faculty"("facultyName");


--
-- Name: SCHEMA public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- Name: TABLE "1151302123"; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE public."1151302123" FROM PUBLIC;
REVOKE ALL ON TABLE public."1151302123" FROM postgres;
GRANT ALL ON TABLE public."1151302123" TO postgres;
GRANT ALL ON TABLE public."1151302123" TO PUBLIC;


--
-- Name: TABLE "1151302123trimesterTaken"; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE public."1151302123trimesterTaken" FROM PUBLIC;
REVOKE ALL ON TABLE public."1151302123trimesterTaken" FROM postgres;
GRANT ALL ON TABLE public."1151302123trimesterTaken" TO postgres;
GRANT ALL ON TABLE public."1151302123trimesterTaken" TO PUBLIC;


--
-- Name: TABLE "1161301595"; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE public."1161301595" FROM PUBLIC;
REVOKE ALL ON TABLE public."1161301595" FROM postgres;
GRANT ALL ON TABLE public."1161301595" TO postgres;
GRANT ALL ON TABLE public."1161301595" TO PUBLIC;


--
-- Name: TABLE "1161301595trimesterTaken"; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE public."1161301595trimesterTaken" FROM PUBLIC;
REVOKE ALL ON TABLE public."1161301595trimesterTaken" FROM postgres;
GRANT ALL ON TABLE public."1161301595trimesterTaken" TO postgres;
GRANT ALL ON TABLE public."1161301595trimesterTaken" TO PUBLIC;


--
-- Name: TABLE "1161302847"; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE public."1161302847" FROM PUBLIC;
REVOKE ALL ON TABLE public."1161302847" FROM postgres;
GRANT ALL ON TABLE public."1161302847" TO postgres;
GRANT ALL ON TABLE public."1161302847" TO PUBLIC;


--
-- Name: TABLE "1161302847trimesterTaken"; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE public."1161302847trimesterTaken" FROM PUBLIC;
REVOKE ALL ON TABLE public."1161302847trimesterTaken" FROM postgres;
GRANT ALL ON TABLE public."1161302847trimesterTaken" TO postgres;
GRANT ALL ON TABLE public."1161302847trimesterTaken" TO PUBLIC;


--
-- Name: TABLE "1161303847trimesterTaken"; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE public."1161303847trimesterTaken" FROM PUBLIC;
REVOKE ALL ON TABLE public."1161303847trimesterTaken" FROM postgres;
GRANT ALL ON TABLE public."1161303847trimesterTaken" TO postgres;
GRANT ALL ON TABLE public."1161303847trimesterTaken" TO PUBLIC;


--
-- Name: TABLE "1161303848"; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE public."1161303848" FROM PUBLIC;
REVOKE ALL ON TABLE public."1161303848" FROM postgres;
GRANT ALL ON TABLE public."1161303848" TO postgres;
GRANT ALL ON TABLE public."1161303848" TO PUBLIC;


--
-- Name: TABLE "1161303848trimesterTaken"; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE public."1161303848trimesterTaken" FROM PUBLIC;
REVOKE ALL ON TABLE public."1161303848trimesterTaken" FROM postgres;
GRANT ALL ON TABLE public."1161303848trimesterTaken" TO postgres;
GRANT ALL ON TABLE public."1161303848trimesterTaken" TO PUBLIC;


--
-- Name: TABLE "1171300038"; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE public."1171300038" FROM PUBLIC;
REVOKE ALL ON TABLE public."1171300038" FROM postgres;
GRANT ALL ON TABLE public."1171300038" TO postgres;
GRANT ALL ON TABLE public."1171300038" TO PUBLIC;


--
-- Name: TABLE "1171300038trimesterTaken"; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE public."1171300038trimesterTaken" FROM PUBLIC;
REVOKE ALL ON TABLE public."1171300038trimesterTaken" FROM postgres;
GRANT ALL ON TABLE public."1171300038trimesterTaken" TO postgres;
GRANT ALL ON TABLE public."1171300038trimesterTaken" TO PUBLIC;


--
-- Name: TABLE "1171500058"; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE public."1171500058" FROM PUBLIC;
REVOKE ALL ON TABLE public."1171500058" FROM postgres;
GRANT ALL ON TABLE public."1171500058" TO postgres;
GRANT ALL ON TABLE public."1171500058" TO PUBLIC;


--
-- Name: TABLE "1171500058trimesterTaken"; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE public."1171500058trimesterTaken" FROM PUBLIC;
REVOKE ALL ON TABLE public."1171500058trimesterTaken" FROM postgres;
GRANT ALL ON TABLE public."1171500058trimesterTaken" TO postgres;
GRANT ALL ON TABLE public."1171500058trimesterTaken" TO PUBLIC;


--
-- Name: TABLE "18/19"; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE public."18/19" FROM PUBLIC;
REVOKE ALL ON TABLE public."18/19" FROM postgres;
GRANT ALL ON TABLE public."18/19" TO postgres;
GRANT ALL ON TABLE public."18/19" TO PUBLIC;


--
-- Name: TABLE "18/19-1"; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE public."18/19-1" FROM PUBLIC;
REVOKE ALL ON TABLE public."18/19-1" FROM postgres;
GRANT ALL ON TABLE public."18/19-1" TO postgres;
GRANT ALL ON TABLE public."18/19-1" TO PUBLIC;


--
-- Name: TABLE "Faculty"; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE public."Faculty" FROM PUBLIC;
REVOKE ALL ON TABLE public."Faculty" FROM postgres;
GRANT ALL ON TABLE public."Faculty" TO postgres;
GRANT ALL ON TABLE public."Faculty" TO PUBLIC;


--
-- Name: TABLE "Trimester"; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE public."Trimester" FROM PUBLIC;
REVOKE ALL ON TABLE public."Trimester" FROM postgres;
GRANT ALL ON TABLE public."Trimester" TO postgres;
GRANT ALL ON TABLE public."Trimester" TO PUBLIC;


--
-- Name: TABLE "User"; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE public."User" FROM PUBLIC;
REVOKE ALL ON TABLE public."User" FROM postgres;
GRANT ALL ON TABLE public."User" TO postgres;
GRANT ALL ON TABLE public."User" TO PUBLIC;


--
-- Name: DEFAULT PRIVILEGES FOR TABLES; Type: DEFAULT ACL; Schema: -; Owner: postgres
--

ALTER DEFAULT PRIVILEGES FOR ROLE postgres REVOKE ALL ON TABLES  FROM PUBLIC;
ALTER DEFAULT PRIVILEGES FOR ROLE postgres REVOKE ALL ON TABLES  FROM postgres;
ALTER DEFAULT PRIVILEGES FOR ROLE postgres GRANT ALL ON TABLES  TO postgres;
ALTER DEFAULT PRIVILEGES FOR ROLE postgres GRANT ALL ON TABLES  TO PUBLIC;


--
-- PostgreSQL database dump complete
--

