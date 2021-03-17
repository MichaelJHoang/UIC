name := "jhoang6_cs474_homework3"

version := "0.1"

scalaVersion := "2.13.1"

lazy val jhoang6_cs474_homework3 = (project in file("."))
        .settings(
            name := "jhoang6_cs474_homework3",
            libraryDependencies ++= Seq(
                "com.typesafe" % "config" % "1.3.4", //typesafe
                // logback
                "com.typesafe.scala-logging" %% "scala-logging" % "3.9.2",
                "ch.qos.logback" % "logback-classic" % "1.2.3",
                // unit testing, junit
                "org.scalactic" %% "scalactic" % "3.0.8",
                "org.scalatest" %% "scalatest" % "3.0.8" % "test",
                "junit" % "junit" % "4.11" % Test,
                "com.novocode" % "junit-interface" % "0.10-M4" % "test",
            ),
            compileOrder := CompileOrder.JavaThenScala
        )