		if (pthread_create(&info->tid[i], NULL, &routine, NULL))
		{
			ft_error("Error creating threads\n");
			return (false);
		}